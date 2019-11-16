/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_inf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:29:36 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/16 16:06:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TILE_INF_H
# define TILE_INF_H

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

typedef struct	s_tile_inf
{
	t_tile_id	id;
	size_t		row;
	size_t		col;
}				t_tile_inf;

typedef enum	e_portal_type
{
	FIRST_PORTAL,
	SECOND_PORTAL
}				t_portal_type;

typedef struct	s_portal_inf
{
	t_portal_type	type;
	t_direction		dir;
}				t_portal_inf;

typedef union	u_tile_data
{
	t_portal_inf	portal_inf;
}				t_tile_data;

typedef struct	s_tile_meta
{
	t_tile_id	id;
	t_tile_data	data;
}				t_tile_meta;

#endif
