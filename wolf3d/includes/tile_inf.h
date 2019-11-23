/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_inf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:29:36 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/25 11:31:32 by gguichar         ###   ########.fr       */
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
	TILE_DOOR_HORIZONTAL = 2,
	TILE_DOOR_VERTICAL = 3,
	TILE_LAST = 4,
	TILE_UNKNOWN
}				t_tile_id;

typedef enum	e_tile_data_type
{
	NO_DATA,
	PORTAL_DATA,
	DOOR_DATA
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

typedef struct	s_portal_inf
{
	t_portal_type	type;
	t_direction		dir;
	int				target;
}				t_portal_inf;

typedef enum	e_door_state
{
	DOOR_CLOSED,
	DOOR_OPENED,
	DOOR_OPENING,
	DOOR_CLOSING
}				t_door_state;

typedef struct	s_door_inf
{
	t_door_state	state;
	double			progress;
}				t_door_inf;

typedef union	u_tile_data
{
	t_portal_inf	portal;
	t_door_inf		door;
}				t_tile_data;

typedef struct	s_tile_meta
{
	t_tile_id			id;
	t_vec2i				pos;
	t_tile_data_type	type;
	t_tile_data			data;
}				t_tile_meta;

#endif
