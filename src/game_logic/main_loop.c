/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 02:24:05 by cababou           #+#    #+#             */
/*   Updated: 2019/01/17 23:29:01 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

void	gameloop(t_wolf *wolf)
{
	Uint32	time;

	while (1)
	{
		wolf->lastFrame = SDL_GetTicks();
		while (SDL_PollEvent(&wolf->last_event))
		{
			printf("Event type : %d\n", wolf->last_event.type);
			if (wolf->last_event.type == SDL_KEYDOWN
				|| wolf->last_event.type == SDL_KEYUP)
				distribute_events(wolf, wolf->last_event);
		}
		time = (SDL_GetTicks() - wolf->lastFrame);
		SDL_Delay(time > FRAMERATE ? 0 : FRAMERATE - time);
	}
}
