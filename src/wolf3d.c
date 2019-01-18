/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 22:37:39 by cababou           #+#    #+#             */
/*   Updated: 2019/01/18 00:10:53 by cababou          ###   ########.fr       */
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
	else if (code == ERROR_SDL_INIT)
		quit("Couldn't initalize SDL.", code);
	else if (code == ERROR_SDL_WINDOW_INIT)
		quit("Couldn't initialize SDL window", code);
	else
		quit("Exiting Wolf3D", code);
}

void	bind_events(t_wolf *wolf)
{
	register_event(wolf, SDL_QUIT, quit_event);
}

void	init_sdl(t_wolf *wolf)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		exit_program(ERROR_SDL_INIT);
	if ((wolf->window = SDL_CreateWindow("W3D", 5, 5,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN)) <= 0)
		exit_program(ERROR_SDL_WINDOW_INIT);
	wolf->surface = SDL_GetWindowSurface(wolf->window);
}

int		main(int argc, char **argv)
{
	t_wolf	*wolf;

	if ((wolf = malloc(sizeof(t_wolf))) == NULL)
		exit_program(ERROR_MEMORY);
	init_sdl(wolf);
	init_events(wolf);
	bind_events(wolf);
	gameloop(wolf);
	return (0);
}
