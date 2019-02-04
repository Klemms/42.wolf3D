/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 23:38:15 by cababou           #+#    #+#             */
/*   Updated: 2019/02/01 14:13:44 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

int		close_window(t_wolf *w)
{
	exit_program(0);
	return (0);
}

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
		quit("Couldn't initalize MLX.", code);
	else if (code == ERROR_MLX_WINDOW_INIT)
		quit("Couldn't initialize MLX window.", code);
	else if (code == ERROR_NOT_ENOUGH_ARGS)
		quit("Not enough arguments.", code);
	else
		quit("Exiting Wolf3D", code);
}
