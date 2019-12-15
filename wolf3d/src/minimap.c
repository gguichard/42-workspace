/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:55:28 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/15 13:41:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <string.h>
#include <stdint.h>
#include "wolf3d.h"
#include "vec2.h"
#include "tile_inf.h"

static int		minimap_plot_px(t_ctx *ctx, size_t idx, uint32_t color
	, int z_value)
{
	if (ctx->minimap.z_buffer[idx] < z_value)
	{
		ctx->minimap.pixels[idx] = color;
		ctx->minimap.z_buffer[idx] = z_value;
		return (1);
	}
	return (0);
}

static t_vec2d	minimap_to_map_pos(t_ctx *ctx, t_vec2i pos)
{
	t_vec2d	block_pos;

	block_pos = vec2d(pos.x, pos.y);
	block_pos = vec2d_mulf(block_pos, 1 / (double)ctx->minimap.size);
	block_pos = vec2d_sub(block_pos, vec2d(0.5, 0.5));
	block_pos = vec2d_mulf(block_pos, ctx->minimap.view_radius);
	block_pos = vec2d_add(block_pos, ctx->player.position);
	return (block_pos);
}

static int		minimap_wall_plot(t_ctx *ctx, size_t idx, t_tile_meta *tile_meta
	, t_vec2d block_pos)
{
	double		dumb;
	t_vec2d		new_pos;
	uint32_t	color;

	if (tile_meta->type == PORTAL_DATA)
	{
		new_pos = vec2d(modf(block_pos.x, &dumb), modf(block_pos.y, &dumb));
		if ((tile_meta->data.portal.dir == NORTH
				&& new_pos.x < PLAYER_HALF_SIZE)
			|| (tile_meta->data.portal.dir == SOUTH
				&& new_pos.x >= (1 - PLAYER_HALF_SIZE))
			|| (tile_meta->data.portal.dir == WEST
				&& new_pos.y < PLAYER_HALF_SIZE)
			|| (tile_meta->data.portal.dir == EAST
				&& new_pos.y >= (1 - PLAYER_HALF_SIZE)))
		{
			if (tile_meta->data.portal.type == ENTRY_PORTAL)
				color = MINIMAP_PORTAL_ENTRY_COLOR;
			else
				color = MINIMAP_PORTAL_EXIT_COLOR;
			return (minimap_plot_px(ctx, idx, color, 50));
		}
	}
	return (minimap_plot_px(ctx, idx, MINIMAP_WALL_COLOR, 50));
}

static int		minimap_plot(t_ctx *ctx, t_vec2i pos)
{
	size_t		idx;
	t_vec2d		block_pos;
	t_tile_meta	*tile_meta;

	idx = pos.y * ctx->minimap.size + pos.x;
	if (pos.x < MINIMAP_BORDER || pos.y < MINIMAP_BORDER
		|| pos.x >= (ctx->minimap.size - MINIMAP_BORDER)
		|| pos.y >= (ctx->minimap.size - MINIMAP_BORDER))
		return (minimap_plot_px(ctx, idx, MINIMAP_BORDER_COLOR, 100));
	block_pos = minimap_to_map_pos(ctx, pos);
	if (block_pos.x < 0 || block_pos.y < 0
		|| block_pos.x >= ctx->tile_map.width
		|| block_pos.y >= ctx->tile_map.height)
		return (minimap_plot_px(ctx, idx, MINIMAP_OUTSIDE_COLOR, 50));
	tile_meta = &ctx->tile_map.tiles[(int)block_pos.y * ctx->tile_map.width
		+ (int)block_pos.x];
	if (tile_meta->id != TILE_EMPTY)
		return (minimap_wall_plot(ctx, idx, tile_meta, block_pos));
	else if (fabs(block_pos.x - ctx->player.position.x) < PLAYER_HALF_SIZE
		&& fabs(block_pos.y - ctx->player.position.y) < PLAYER_HALF_SIZE)
		return (minimap_plot_px(ctx, idx, MINIMAP_PLAYER_COLOR, 10));
	else
		return (minimap_plot_px(ctx, idx, FLOOR_COLOR, 0));
}

void			minimap_background(t_ctx *ctx)
{
	t_vec2i	pos;

	pos = vec2i(0, 0);
	while (pos.x < ctx->minimap.size)
	{
		pos.y = 0;
		while (pos.y < ctx->minimap.size)
		{
			minimap_plot(ctx, pos);
			pos.y += 1;
		}
		pos.x += 1;
	}
}
