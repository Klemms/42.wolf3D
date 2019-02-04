/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 13:20:21 by hdussert          #+#    #+#             */
/*   Updated: 2019/02/04 09:41:44 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		hooks(t_wolf *w)
{
	mlx_hook(w->window, KeyPress, KeyPressMask, key_down, w);
	mlx_hook(w->window, KeyRelease, KeyReleaseMask, key_up, w);
	mlx_hook(w->window, DestroyNotify, NoEventMask, close_window, w);
	mlx_loop_hook(w->mlx, loop, w);
}

int			main(int argc, char *argv[])
{
	t_wolf	*wolf;

	if (argc == 6)
	{
		wolf = init_wolf();
		init_mlx(wolf);
		if (!parsing(argv[1], wolf->map))
			return (0);
		if (!init_texture(wolf, argv))
		{
			ft_putstr("Invalid texture file(s), (.xpm only).\n");
			return (0);
		}
		wolf->you = new_player(wolf->map);
		hooks(wolf);
		mlx_loop(wolf->mlx);
	}
	else
		exit_program(ERROR_NOT_ENOUGH_ARGS);
	return (0);
}
