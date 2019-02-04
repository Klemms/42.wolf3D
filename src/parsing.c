/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 11:21:38 by hdussert          #+#    #+#             */
/*   Updated: 2019/01/23 03:50:26 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		is_valid(t_map *map, int fd)
{
	int		i;
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		map->height++;
		i = -1;
		while (line[++i] && line[i] != '\n')
		{
			if (line[i] != '#' && line[i] != '.')
			{
				free(line);
				return (0);
			}
		}
		if (i > map->width)
			map->width = (i > map->width ? i : map->width);
		free(line);
	}
	map->height += 2;
	map->width += 2;
	close(fd);
	return (1);
}

static int		fill(t_map *map, int fd)
{
	int		i;
	int		j;
	char	*line;

	if (!(map->m = (char **)malloc(sizeof(char *) * map->height + 1)))
		exit_program(ERROR_MEMORY);
	map->m[map->height] = NULL;
	j = 0;
	line = NULL;
	while (get_next_line(fd, &line))
	{
		if (!(map->m[++j] = (char *)malloc(sizeof(char) * map->width + 1)))
			exit_program(ERROR_MEMORY);
		i = -1;
		while (line[++i])
			map->m[j][i + 1] = line[i];
		i--;
		while (++i < map->width - 2)
			map->m[j][i + 1] = '#';
		map->m[j][map->width] = '\0';
		free(line);
	}
	close(fd);
	return (1);
}

static void		contour(t_map *map)
{
	int		i;
	int		width;
	int		height;

	width = map->width;
	height = map->height;
	i = -1;
	if (!(map->m[0] = (char *)malloc(sizeof(char) * width + 1))
	|| !(map->m[height - 1] = (char *)malloc(sizeof(char) * width + 1)))
		exit_program(ERROR_MEMORY);
	while (++i < width)
	{
		map->m[0][i] = '#';
		map->m[height - 1][i] = '#';
	}
	i = -1;
	while (++i < height)
	{
		map->m[i][0] = '#';
		map->m[i][width - 1] = '#';
	}
	map->m[0][width] = '\0';
	map->m[height - 1][width] = '\0';
}

static int		startpos(t_map *map, char c)
{
	int		x;
	int		y;

	y = map->height;
	while (--y >= 0 && map->start_x == 0)
	{
		x = map->width;
		while (--x >= 0 && map->start_x == 0)
		{
			if (map->m[y][x] == c)
			{
				map->start_x = x;
				map->start_y = y;
			}
		}
	}
	return (map->start_x != 0);
}

int				parsing(char *file, t_map *map)
{
	int		fd[2];

	if ((fd[0] = open(file, O_RDONLY)) < 2
	|| (read(fd[0], NULL, 0) < 0))
		exit_program(ERROR_MEMORY);
	fd[1] = open(file, O_RDONLY);
	if (is_valid(map, fd[0]))
	{
		fill(map, fd[1]);
		contour(map);
		if (!startpos(map, '.'))
			return (0);
		return (1);
	}
	return (0);
}
