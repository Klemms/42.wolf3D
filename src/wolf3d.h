/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:43:48 by cababou           #+#    #+#             */
/*   Updated: 2019/02/01 14:13:41 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <time.h>
# include <Tk/X11/X.h>
# include "../libft/libft.h"
# include "errors/errors.h"

typedef struct		s_image
{
	void		*ptr;
	char		*img;
	int			bpp;
	int			s_l;
	int			endian;
}					t_image;

typedef struct		s_vec
{
	double	x;
	double	y;
	double	z;
}					t_vec;

typedef struct		s_line
{
	t_vec	cur;
	t_vec	dir;
	t_vec	inc;
	int		color;
}					t_line;

typedef struct		s_player
{
	t_vec		*pos;
	t_vec		*dir;
	t_vec		*plane;
	double		speed;
	double		rotspeed;
	int			rov;
}					t_player;

typedef struct		s_map
{
	int		width;
	int		height;
	int		start_x;
	int		start_y;
	char	**m;
}					t_map;

typedef struct		s_key
{
	int		left;
	int		right;
	int		up;
	int		down;
	int		shadow;
}					t_key;

typedef struct		s_texture
{
	t_image		img;
	int			height;
	int			width;
}					t_texture;

typedef struct		s_wolf
{
	void			*mlx;
	void			*window;
	int				w_width;
	int				w_height;
	char			*w_title;
	t_image			*image;
	t_map			*map;
	t_player		*you;
	t_key			*keys;
	clock_t			oldtime;
	clock_t			curtime;
	double			fps;
	t_texture		texture[4];
	int				temp_color;
}					t_wolf;

typedef struct		s_sight
{
	double	camera_x;
	t_vec	ray_dir;
	t_vec	*pos;
	t_vec	side_dist;
	t_vec	delta_dist;
	double	perp_wall_dist;
	t_vec	step;
	int		hit;
	int		cpt;
	int		rov;
	int		side;
	int		tex;
}					t_sight;

t_wolf				*init_wolf();
void				init_mlx(t_wolf *w);
t_image				*new_screen_image(t_wolf *w);

int					init_texture(t_wolf *w, char *argv[]);

t_player			*new_player(t_map *map);
int					draw(t_wolf *w);
int					parsing(char *file, t_map *map);
int					key_down(int key, t_wolf *w);
int					key_up(int key, t_wolf *w);
void				line(t_wolf *w, t_vec *start, t_vec *end, int color);
t_vec				*new_vec(double x, double y, double z);
int					loop(t_wolf *w);
void				calc_lov(t_wolf *w);
void				init_sight(t_wolf *w, t_sight *p, double x, t_player *you);
void				pixel_put(t_wolf *w, char *ptr, int x, int y);

void				exit_program(int code);
void				quit(char *message, int code);
int					close_window(t_wolf *w);
#endif
