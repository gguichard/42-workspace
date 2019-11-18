/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:24:26 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/19 08:34:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "wolf3d.h"
#include "map_inf.h"
#include "tile_inf.h"
#include "vec2.h"
#include "error.h"

static int		parse_tile_id(const char *tile)
{
	t_tile_id	tile_id;
	long long	tile_long;
	char		*endptr;

	tile_id = TILE_UNKNOWN;
	if (ft_strequ(tile, ">"))
		tile_id = TILE_PLAYER_NORTH;
	else if (ft_strequ(tile, "v"))
		tile_id = TILE_PLAYER_EAST;
	else if (ft_strequ(tile, "^"))
		tile_id = TILE_PLAYER_WEST;
	else if (ft_strequ(tile, "<"))
		tile_id = TILE_PLAYER_SOUTH;
	else
	{
		tile_long = ft_strtol(tile, &endptr, 10);
		if (*endptr == '\0' && tile_long >= 0 && tile_long < TILE_LAST)
			tile_id = (t_tile_id)tile_long;
	}
	return (tile_id);
}

static size_t	push_tiles(t_vector *tiles, char **positions, size_t row
	, t_error *err)
{
	int			col;
	t_tile_id	tile_id;
	t_tile_inf	*tile_inf;

	*err = ERR_NOERROR;
	col = 0;
	while (positions[col] != NULL)
	{
		tile_id = parse_tile_id(positions[col]);
		if (tile_id == TILE_UNKNOWN)
			return (*err = ERR_MAPTILE);
		tile_inf = (t_tile_inf *)malloc(sizeof(t_tile_inf));
		if (tile_inf == NULL)
			return (*err = ERR_UNEXPECTED);
		tile_inf->row = row;
		tile_inf->col = col;
		tile_inf->id = tile_id;
		if (!ft_vecpush(tiles, tile_inf))
		{
			free(tile_inf);
			return (*err = ERR_UNEXPECTED);
		}
		col++;
	}
	return (col);
}

static t_vector	read_tiles(int fd, t_map_inf *map_inf, t_error *err)
{
	t_vector	tiles;
	char		*line;
	char		**positions;
	int			col;

	*err = ERR_NOERROR;
	ft_memset(&tiles, 0, sizeof(t_vector));
	line = NULL;
	while (*err == ERR_NOERROR && get_next_line(fd, &line) == 1)
	{
		positions = ft_strssplit(line, " \t");
		if (positions == NULL)
			*err = ERR_UNEXPECTED;
		else
		{
			col = push_tiles(&tiles, positions, map_inf->height, err);
			if (*err == ERR_NOERROR && col > map_inf->width)
				map_inf->width = col;
		}
		map_inf->height += 1;
	}
	return (tiles);
}

static void		tiles_vector_to_map(t_vector tiles, t_map_inf *map_inf
	, t_error *err)
{
	size_t		size;
	size_t		idx;
	t_tile_inf	*tile_inf;

	*err = ERR_NOERROR;
	size = map_inf->width * map_inf->height * sizeof(*map_inf->tiles);
	map_inf->tiles = (t_tile_meta *)malloc(size);
	if (map_inf->tiles == NULL)
		*err = ERR_UNEXPECTED;
	else
	{
		ft_memset(map_inf->tiles, 0, size);
		idx = 0;
		while (idx < tiles.size)
		{
			tile_inf = (t_tile_inf *)tiles.data[idx];
			if (tile_inf->id < 0)
				place_player_map(map_inf, tile_inf);
			map_inf->tiles[tile_inf->col + tile_inf->row * map_inf->width].id =
				tile_inf->id;
			map_inf->tiles[tile_inf->col + tile_inf->row * map_inf->width].pos =
				vec2i(tile_inf->col, tile_inf->row);
			idx++;
		}
	}
}

t_map_inf		load_mapfile(const char *file, t_error *err)
{
	t_map_inf	map_inf;
	int			fd;
	t_vector	tiles;

	ft_memset(&map_inf, 0, sizeof(t_map_inf));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		*err = ERR_ERRNO;
	else
	{
		tiles = read_tiles(fd, &map_inf, err);
		if (*err == ERR_NOERROR)
		{
			tiles_vector_to_map(tiles, &map_inf, err);
			if (!map_inf.has_player)
				*err = ERR_MAPNOPLAYER;
		}
		ft_vecfree(&tiles);
		close(fd);
	}
	return (map_inf);
}
