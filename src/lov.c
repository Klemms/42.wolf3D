/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 11:20:18 by hdussert          #+#    #+#             */
/*   Updated: 2019/01/23 03:39:58 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int					calc_column(t_sight *p, t_wolf *w, int tex)
{
	double	col;

	if (p->side == 1)
		col = p->pos->x + p->perp_wall_dist * p->ray_dir.x;
	else
		col = p->pos->y + p->perp_wall_dist * p->ray_dir.y;
	col = col - floor(col);
	col = round(col * (double)(w->texture[tex].width - 1));
	if ((p->side == 0 && p->ray_dir.x > 0)
	|| (p->side == 1 && p->ray_dir.y < 0))
		col = w->texture[tex].width - col - 1;
	return (col);
}

void				calc_perp_dist(t_sight *p, t_player *you)
{
	//Calculate distance projected on camera direction
	//(Euclidean distance will give fisheye effect!)
	if (p->side == 0)
		p->perp_wall_dist = ((int)p->pos->x - you->pos->x +
							(1.0 - p->step.x) / 2.0) / p->ray_dir.x;
	else
		p->perp_wall_dist = ((int)p->pos->y - you->pos->y +
							(1.0 - p->step.y) / 2.0) / p->ray_dir.y;
}

void				draw_wall(t_wolf *w, t_sight *p, double x, int column,
							int tex)
{
	double	line_height;
	int		draw_start;
	int		draw_end;
	int		py;
	int		wall_size;

	calc_perp_dist(p, w->you);
	//Calculate height of line to draw on screen
	line_height = (int)(w->w_height / p->perp_wall_dist);
	//calculate lowest and highest pixel to fill in current stripe
	draw_start = -line_height / 2 + w->w_height / 2;
	draw_end = line_height / 2 + w->w_height / 2;
	wall_size = draw_end - draw_start;
	//draw the pixels of the stripe as a vertical line
	py = draw_start;
	py = (py < 0 ? 0 : py);
	draw_end = (draw_end > w->w_height ? w->w_height - 1 : draw_end);
	if (p->hit)
	{
		while (py < draw_end)//(draw_start > draw_end ? draw_start : draw_end))
		{
			line_height = (py - draw_start) / (double)wall_size;
			w->temp_color = ((int *)w->texture[tex].img.img)[column +
			(int)round(line_height * (w->texture[tex].height - 1)) *
			w->texture[tex].width];
			pixel_put(w, w->image->img, x, py);
			py++;
		}
	}
}

int					see_wall(t_sight *p, t_wolf *w)
{
	p->hit = 0;
	p->cpt = 0;
	while (p->hit == 0 && p->cpt < p->rov)
	{
//jump to next map square, OR in x-direction, OR in y-direction
		if (p->side_dist.x < p->side_dist.y)
		{
			p->side_dist.x += p->delta_dist.x;
			p->pos->x += p->step.x;
			p->side = 0;
		}
		else
		{
			p->side_dist.y += p->delta_dist.y;
			p->pos->y += p->step.y;
			p->side = 1;
		}
//Check if ray has hit a wall
		if (p->pos->x >= 0 && p->pos->x < w->map->width
		&& p->pos->y >= 0 && p->pos->y < w->map->height
		&& w->map->m[(int)p->pos->y][(int)p->pos->x] == '#')
			break ;
		p->cpt += 1;
	}
	return (p->cpt < p->rov ? (p->hit = 1) : 0);
}

void				calc_lov(t_wolf *w)
{
	t_sight	p;
	int		x;
	int		column;
	int		tex;

	x = 0;
	while (x < w->w_width)
	{
		init_sight(w, &p, x, w->you);
		if (see_wall(&p, w))
		{
			if (p.side == 1)
				tex = p.step.y < 0;
			else
				tex = (p.step.x < 0 ? 2 : 3);
			column = calc_column(&p, w, tex);
			draw_wall(w, &p, x, column, tex);
		}
		x++;
		free(p.pos);
	}
}
