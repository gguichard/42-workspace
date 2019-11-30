/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_inf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:29:36 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/30 23:43:13 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TILE_INF_H
# define TILE_INF_H

# include "vec2.h"
# include "direction.h"

typedef enum	e_tile_id
{
	TILE_PLAYER_NORTH = -1,
	TILE_PLAYER_EAST = -2,
	TILE_PLAYER_WEST = -3,
	TILE_PLAYER_SOUTH = -4,
	TILE_EMPTY = 0,
	TILE_WALL = 1,
	TILE_LAST = 2,
	TILE_UNKNOWN
}				t_tile_id;

typedef enum	e_tile_data_type
{
	NO_DATA,
	PORTAL_DATA
}				t_tile_data_type;

typedef struct	s_tile_inf
{
	t_tile_id	id;
	size_t		row;
	size_t		col;
}				t_tile_inf;

typedef enum	e_portal_type
{
	ENTRY_PORTAL,
	EXIT_PORTAL
}				t_portal_type;

typedef struct s_tile_meta	t_tile_meta;

typedef struct	s_portal_inf
{
	t_portal_type	type;
	t_direction		dir;
	t_tile_meta		*target;
}				t_portal_inf;

typedef union	u_tile_data
{
	t_portal_inf	portal;
}				t_tile_data;

struct			s_tile_meta
{
	t_tile_id			id;
	t_vec2i				pos;
	t_tile_data_type	type;
	t_tile_data			data;
};

#endif
