/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 23:44:05 by cababou           #+#    #+#             */
/*   Updated: 2019/02/01 13:43:18 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

t_wolf	*init_wolf(void)
{
	t_wolf *w;

	if (!(w = malloc(sizeof(t_wolf)))
		|| !(w->keys = (t_key *)malloc(sizeof(t_key)))
		|| !(w->map = (t_map *)malloc(sizeof(t_map))))
		exit_program(ERROR_MEMORY);
	w->w_width = 800;
	w->w_height = 600;
	w->w_title = "Wolf 3D";
	w->map->height = 0;
	w->map->width = 0;
	w->map->start_x = 0;
	w->map->start_y = 0;
	w->keys->left = 0;
	w->keys->right = 0;
	w->keys->up = 0;
	w->keys->down = 0;
	w->keys->shadow = 0;
	w->oldtime = 0;
	w->curtime = 0;
	w->fps = 60.0;
	return (w);
}

void	init_mlx(t_wolf *w)
{
	if (!(w->mlx = mlx_init()))
		exit_program(ERROR_MLX_INIT);
	if (!(w->window = mlx_new_window(w->mlx, w->w_width, w->w_height,
		w->w_title)))
		exit_program(ERROR_MLX_WINDOW_INIT);
	w->image = new_screen_image(w);
}
