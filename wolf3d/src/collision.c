/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 11:37:22 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/20 17:26:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf3d.h"
#include "player.h"
#include "vec2.h"
#include "tile_inf.h"
#include "direction.h"

static int	is_wall(int x, int y, t_map_inf *map_inf, t_direction dir)
{
	t_tile_meta	*tile;

	if (x < 0 || y < 0 || x >= map_inf->width || y >= map_inf->height)
		return (1);
	else
	{
		tile = &map_inf->tiles[y * map_inf->width + x];
		return (tile->id != TILE_EMPTY
			&& (tile->type != PORTAL_DATA || tile->data.portal.dir != dir));
	}
}

void		check_collision_after_move(t_ctx *ctx, t_vec2d old_pos)
{
	t_vec2d		pos;
	t_vec2d		dir;
	t_direction	coll_dir;
	t_tile_meta	*tile;

	pos = ctx->player.position;
	dir = vec2d_sub(pos, old_pos);
	if (fabs(dir.x) > fabs(dir.y))
		coll_dir = (dir.x > 0) ? NORTH : SOUTH;
	else
		coll_dir = (dir.y > 0) ? WEST : EAST;
	if (pos.x >= 0 && pos.y >= 0
		&& pos.x < ctx->tile_map.width && pos.y < ctx->tile_map.height)
	{
		tile = &ctx->tile_map.tiles[(int)pos.y * ctx->tile_map.width
			+ (int)pos.x];
		if (tile->type == PORTAL_DATA
			&& tile->data.portal.target != -1
			&& tile->data.portal.dir == coll_dir)
		{
			teleport_through_portal(ctx, tile);
			return ;
		}
	}
	if (dir.x > 0
		&& is_wall(pos.x + PLAYER_HALF_SIZE, old_pos.y, &ctx->tile_map, NORTH))
		pos.x = floor(pos.x + PLAYER_HALF_SIZE) - PLAYER_HALF_SIZE;
	else if (dir.x < 0
		&& is_wall(pos.x - PLAYER_HALF_SIZE, old_pos.y, &ctx->tile_map, SOUTH))
		pos.x = floor(pos.x - PLAYER_HALF_SIZE + 1) + PLAYER_HALF_SIZE;
	if (dir.y > 0
		&& is_wall(pos.x, pos.y + PLAYER_HALF_SIZE, &ctx->tile_map, WEST))
		pos.y = floor(pos.y + PLAYER_HALF_SIZE) - PLAYER_HALF_SIZE;
	else if (dir.y < 0
		&& is_wall(pos.x, pos.y - PLAYER_HALF_SIZE, &ctx->tile_map, EAST))
		pos.y = floor(pos.y - PLAYER_HALF_SIZE + 1) + PLAYER_HALF_SIZE;
	ctx->player.position = pos;
}
