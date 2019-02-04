/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 03:30:59 by cababou           #+#    #+#             */
/*   Updated: 2019/01/23 03:33:50 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_sight(t_wolf *w, t_sight *p, double x, t_player *you)
{
	//calculate ray position and direction
	p->camera_x = 2.0 * x / (double)(w->w_width) - 1.0; //x-coordinate in camera space
	p->ray_dir.x = you->dir->x + you->plane->x * p->camera_x;
	p->ray_dir.y = you->dir->y + you->plane->y * p->camera_x;
	p->step.x = (p->ray_dir.x < 0 ? -1 : 1);
	p->step.y = (p->ray_dir.y < 0 ? -1 : 1);
	p->pos = new_vec(you->pos->x, you->pos->y, 0);
	p->rov = you->rov;
	//length of ray from one x or y-side to next x or y-side
	p->delta_dist.x = fabs(1 / p->ray_dir.x);
	p->delta_dist.y = fabs(1 / p->ray_dir.y);
	//calculate p->step and initial p->sideDist
	p->side_dist.x = (p->ray_dir.x < 0 ?
					(you->pos->x - (int)p->pos->x) * p->delta_dist.x :
					((int)p->pos->x + 1.0 - you->pos->x) * p->delta_dist.x);
	p->side_dist.y = (p->ray_dir.y < 0 ?
					(you->pos->y - (int)p->pos->y) * p->delta_dist.y :
					((int)p->pos->y + 1.0 - you->pos->y) * p->delta_dist.y);
}
