/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 03:50:49 by cababou           #+#    #+#             */
/*   Updated: 2018/12/14 04:08:09 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

void	init_keys(t_wolf *wolf)
{
	if ((wolf->keys_events = lstcontainer_new()) == NULL)
		exit_program(ERROR_MEMORY);
}

void	register_key_event(t_wolf *wolf, int key, char (*handler)(t_wolf *w))
{
	t_key_event	*event;

	if ((event = malloc(sizeof(t_key_event))) == NULL)
		exit_program(ERROR_MEMORY);
	event->key = key;
	event->handler = handler;
	lstcontainer_add(wolf->keys_events, event);
}

int		handler_keypress(int key, t_wolf *wolf)
{
	/*ft_putnbr(key);
	ft_putendl("");*/



	return (1);
}
