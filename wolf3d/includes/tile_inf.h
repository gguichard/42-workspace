/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_inf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:29:36 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/27 22:25:00 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TILE_INF_H
# define TILE_INF_H

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

#endif
