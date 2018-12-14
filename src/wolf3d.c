/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 22:37:39 by cababou           #+#    #+#             */
/*   Updated: 2018/12/14 04:08:38 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	quit(char *message, int code)
{
	ft_putendl(message);
	exit(code);
}

void	exit_program(int code)
{
	if (code == ERROR_GENERIC)
		quit("An error occured.", code);
	else if (code == ERROR_MEMORY)
		quit("A memory error occured.", code);
	else if (code == ERROR_MLX_INIT)
		quit("Couldn't initalize mlx.", code);
	else if (code == ERROR_MLX_WINDOW_INIT)
		quit("Couldn't initialize mlx window", code);
	else
		quit("Exiting Wolf3D", code);
}

void	bind_events(t_wolf *wolf)
{
	mlx_hook(wolf->main_win, KeyPress, KeyPressMask, handler_keypress, wolf);
}

void	init_mlx(t_wolf *wolf)
{
	if ((wolf->mlx = mlx_init()) == NULL)
		exit_program(ERROR_MLX_INIT);
	if ((wolf->main_win = mlx_new_window(wolf->mlx, 1366, 768, "W3D")) == NULL)
		exit_program(ERROR_MLX_WINDOW_INIT);
}

int		main(int argc, char **argv)
{
	t_wolf	*wolf;

	if ((wolf = malloc(sizeof(t_wolf))) == NULL)
		exit_program(ERROR_MEMORY);
	init_mlx(wolf);
	bind_events(wolf);
	init_keys(wolf);
	mlx_loop(wolf->mlx);
	return (0);
}
