/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 11:37:22 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/28 12:49:09 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf3d.h"
#include "player.h"
#include "vec2.h"
#include "tile_inf.h"
#include "direction.h"

static int	is_side_colliding(t_vec2d player_pos, t_vec2i tile_pos
	, t_map_inf *map_inf, t_direction dir)
{
	t_tile_meta	*tile;

	if (tile_pos.x < 0 || tile_pos.y < 0
		|| tile_pos.x >= map_inf->width || tile_pos.y >= map_inf->height)
		return (1);
	tile = &map_inf->tiles[tile_pos.y * map_inf->width + tile_pos.x];
	if (tile->id == TILE_EMPTY
		|| (tile->type == PORTAL_DATA
			&& tile->data.portal.target != -1
			&& tile->data.portal.dir == dir))
		return (0);
	else if (dir == NORTH)
		return ((player_pos.x - PLAYER_HALF_SIZE) < tile_pos.x
			&& (player_pos.x + PLAYER_HALF_SIZE) > tile_pos.x);
	else if (dir == SOUTH)
		return ((player_pos.x - PLAYER_HALF_SIZE) < (tile_pos.x + 1)
			&& (player_pos.x + PLAYER_HALF_SIZE) > (tile_pos.x + 1));
	else if (dir == WEST)
		return ((player_pos.y - PLAYER_HALF_SIZE) < tile_pos.y
			&& (player_pos.y + PLAYER_HALF_SIZE) > tile_pos.y);
	else if (dir == EAST)
		return ((player_pos.y - PLAYER_HALF_SIZE) < (tile_pos.y + 1)
			&& (player_pos.y + PLAYER_HALF_SIZE) > (tile_pos.y + 1));
	return (1);
}

static int	is_colliding(double x, double y, t_map_inf *map_inf
	, t_direction dir)
{
	t_vec2d	player_pos;
	t_vec2i	start;
	t_vec2i	end;
	t_vec2i	pos;

	player_pos = vec2d(x, y);
	start = vec2i(floor(x - PLAYER_HALF_SIZE), floor(y - PLAYER_HALF_SIZE));
	end = vec2i(ceil(x + PLAYER_HALF_SIZE), ceil(y + PLAYER_HALF_SIZE));
	pos.x = start.x;
	while (pos.x < end.x)
	{
		pos.y = start.y;
		while (pos.y < end.y)
		{
			if (is_side_colliding(player_pos, pos, map_inf, dir))
				return (1);
			pos.y += 1;
		}
		pos.x += 1;
	}
	return (0);
}

void		check_collision_after_move(t_ctx *ctx, t_vec2d old_pos)
{
	t_vec2d		pos;
	t_vec2d		dir;
	t_tile_meta	*tile;

	pos = ctx->player.position;
	dir = vec2d_sub(pos, old_pos);
	if (dir.x > 0
		&& (is_colliding(pos.x, old_pos.y, &ctx->tile_map, NORTH)
			|| is_colliding(pos.x, old_pos.y, &ctx->tile_map, SOUTH)))
		pos.x = floor(pos.x + PLAYER_HALF_SIZE) - PLAYER_HALF_SIZE;
	else if (dir.x < 0
		&& (is_colliding(pos.x, old_pos.y, &ctx->tile_map, NORTH)
			|| is_colliding(pos.x, old_pos.y, &ctx->tile_map, SOUTH)))
		pos.x = floor(pos.x - PLAYER_HALF_SIZE + 1) + PLAYER_HALF_SIZE;
	if (dir.y > 0
		&& (is_colliding(pos.x, pos.y, &ctx->tile_map, WEST)
			|| is_colliding(pos.x, pos.y, &ctx->tile_map, EAST)))
		pos.y = floor(pos.y + PLAYER_HALF_SIZE) - PLAYER_HALF_SIZE;
	else if (dir.y < 0
		&& (is_colliding(pos.x, pos.y, &ctx->tile_map, WEST)
			|| is_colliding(pos.x, pos.y, &ctx->tile_map, EAST)))
		pos.y = floor(pos.y - PLAYER_HALF_SIZE + 1) + PLAYER_HALF_SIZE;
	ctx->player.position = pos;
	if (pos.x >= 0 && pos.y >= 0
		&& pos.x < ctx->tile_map.width
		&& pos.y < ctx->tile_map.height)
	{
		tile = &ctx->tile_map.tiles[(int)pos.y * ctx->tile_map.width + (int)pos.x];
		if (tile->type == PORTAL_DATA && tile->data.portal.target != -1)
			teleport_through_portal(ctx, tile);
	}
}
