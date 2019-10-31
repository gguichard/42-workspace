/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 22:52:50 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/30 11:08:29 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf3d.h"
#include "map_inf.h"
#include "tile_inf.h"

void	place_player_map(t_map_inf *map_inf, t_tile_inf *tile_inf)
{
	map_inf->has_player = 1;
	map_inf->player.position.x = tile_inf->col + .5;
	map_inf->player.position.y = tile_inf->row + .5;
	if (tile_inf->id == TILE_PLAYER_NORTH)
		map_inf->player.angle = 0;
	else if (tile_inf->id == TILE_PLAYER_EAST)
		map_inf->player.angle = -M_PI / 2;
	else if (tile_inf->id == TILE_PLAYER_WEST)
		map_inf->player.angle = M_PI / 2;
	else if (tile_inf->id == TILE_PLAYER_SOUTH)
		map_inf->player.angle = M_PI;
	tile_inf->id = TILE_EMPTY;
}
