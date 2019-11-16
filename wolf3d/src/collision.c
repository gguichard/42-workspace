/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 11:37:22 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/16 16:05:59 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf3d.h"
#include "player.h"
#include "vec2.h"
#include "direction.h"

static int	is_wall(int x, int y, t_map_inf *map_inf)
{
	if (x < 0 || y < 0 || x >= map_inf->width || y >= map_inf->height)
		return (1);
	else
		return (map_inf->tiles[y * map_inf->width + x].id != TILE_EMPTY);
}

void		check_collision_after_move(t_ctx *ctx, t_vec2d old_pos)
{
	t_vec2d	pos;
	t_vec2d	dir;

	pos = ctx->player.position;
	dir = vec2d_sub(pos, old_pos);
	if (dir.x > 0
		&& is_wall(pos.x + PLAYER_HALF_SIZE, old_pos.y, &ctx->tile_map))
		pos.x = floor(pos.x + PLAYER_HALF_SIZE) - PLAYER_HALF_SIZE;
	else if (dir.x < 0
		&& is_wall(pos.x - PLAYER_HALF_SIZE, old_pos.y, &ctx->tile_map))
		pos.x = floor(pos.x - PLAYER_HALF_SIZE + 1) + PLAYER_HALF_SIZE;
	if (dir.y > 0
		&& is_wall(pos.x, pos.y + PLAYER_HALF_SIZE, &ctx->tile_map))
		pos.y = floor(pos.y + PLAYER_HALF_SIZE) - PLAYER_HALF_SIZE;
	else if (dir.y < 0
		&& is_wall(pos.x, pos.y - PLAYER_HALF_SIZE, &ctx->tile_map))
		pos.y = floor(pos.y - PLAYER_HALF_SIZE + 1) + PLAYER_HALF_SIZE;
	ctx->player.position = pos;
}
