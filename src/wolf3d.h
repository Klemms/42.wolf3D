/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 22:37:08 by cababou           #+#    #+#             */
/*   Updated: 2018/12/14 04:08:30 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "mlx.h"
# include "stdlib.h"
# include "errors.h"

# include "events/mappings.h"

# include <Tk/X11/X.h>
# include "../libft/libft.h"

typedef struct			s_wolf
{
	void				*mlx;
	void				*main_win;
	t_lstcontainer		*keys_events;
}						t_wolf;

typedef struct			s_key_event
{
	int					key;
	int					(*handler)(t_wolf *wolf);
}						t_key_event;

void					exit_program(int code);

void					init_keys(t_wolf *wolf);
int						handler_keypress(int key, t_wolf *wolf);
void					register_key_event(t_wolf *wolf, int key,
							char (*handler)(t_wolf *w))

#endif
