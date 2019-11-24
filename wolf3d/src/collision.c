/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 11:37:22 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/25 21:02:45 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf3d.h"
#include "player.h"
#include "vec2.h"
#include "tile_inf.h"
#include "direction.h"

static int	is_wall_colliding(int x, int y, t_map_inf *map_inf, t_direction dir)
{
	t_tile_meta	*tile;

	if (x < 0 || y < 0 || x >= map_inf->width || y >= map_inf->height)
		return (1);
	tile = &map_inf->tiles[y * map_inf->width + x];
	return (tile->id != TILE_EMPTY
		&& (tile->type != PORTAL_DATA || tile->data.portal.dir != dir));
}

static int	is_colliding(double x, double y, t_map_inf *map_inf
	, t_direction dir)
{
	t_vec2i	start;
	t_vec2i	end;
	t_vec2i	pos;

	start = vec2i(x - PLAYER_HALF_SIZE, y - PLAYER_HALF_SIZE);
	end = vec2i(ceil(x + PLAYER_HALF_SIZE), ceil(y + PLAYER_HALF_SIZE));
	pos.x = start.x;
	while (pos.x < end.x)
	{
		pos.y = start.y;
		while (pos.y < end.y)
		{
			if (is_wall_colliding(pos.x, pos.y, map_inf, dir))
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
		tile = &ctx->tile_map.tiles[(int)pos.y * ctx->tile_map.width + (int)pos.x];
		if (tile->type == PORTAL_DATA
			&& tile->data.portal.target != -1
			&& tile->data.portal.dir == coll_dir)
		{
			teleport_through_portal(ctx, tile);
			return ;
		}
	}
	if (dir.x > 0
		&& is_colliding(pos.x, old_pos.y, &ctx->tile_map, coll_dir))
		pos.x = floor(pos.x + PLAYER_HALF_SIZE) - PLAYER_HALF_SIZE;
	else if (dir.x < 0
		&& is_colliding(pos.x, old_pos.y, &ctx->tile_map, coll_dir))
		pos.x = floor(pos.x - PLAYER_HALF_SIZE + 1) + PLAYER_HALF_SIZE;
	if (dir.y > 0
		&& is_colliding(pos.x, pos.y, &ctx->tile_map, coll_dir))
		pos.y = floor(pos.y + PLAYER_HALF_SIZE) - PLAYER_HALF_SIZE;
	else if (dir.y < 0
		&& is_colliding(pos.x, pos.y, &ctx->tile_map, coll_dir))
		pos.y = floor(pos.y - PLAYER_HALF_SIZE + 1) + PLAYER_HALF_SIZE;
	ctx->player.position = pos;
}
