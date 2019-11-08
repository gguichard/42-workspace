/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_view.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:55:28 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/08 16:01:26 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include "wolf3d.h"
#include "minimap.h"
#include "vec2.h"
#include "tile_inf.h"

static uint32_t	minimap_color(t_ctx *ctx, t_vec2i pos, int size
	, int view_radius)
{
	t_vec2d	block_pos;

	block_pos = vec2d(pos.x / (double)size - .5, pos.y / (double)size - .5);
	block_pos = vec2d_scalar(block_pos, view_radius);
	block_pos = vec2d_add(block_pos, ctx->player.position);
	if (block_pos.x < 0 || block_pos.y < 0
		|| block_pos.x >= ctx->tile_map.width
		|| block_pos.y >= ctx->tile_map.height)
		return (0xFFFFFF);
	else if (ctx->tile_map.tiles[(int)block_pos.y * ctx->tile_map.width
			+ (int)block_pos.x] != TILE_EMPTY)
		return (0x000000);
	else if (fabs(block_pos.x - ctx->player.position.x) < PLAYER_HALF_SIZE
		&& fabs(block_pos.y - ctx->player.position.y) < PLAYER_HALF_SIZE)
		return (0xFFFFFF);
	else
		return (0x505050);
}

void			draw_map_view(t_ctx *ctx)
{
	int		map_size;
	int		view_radius;
	t_vec2i	pos;

	map_size = MINIMAP_SIZE * ctx->window.size.width;
	view_radius = ft_min(ft_min(ctx->tile_map.width, ctx->tile_map.height)
			, MINIMAP_VIEW_RADIUS);
	pos = vec2i(0, 0);
	while (pos.x < map_size)
	{
		pos.y = 0;
		while (pos.y < map_size)
		{
			ctx->pixels[pos.y * ctx->window.size.width + pos.x] =
				minimap_color(ctx, pos, map_size, view_radius);
			pos.y += 1;
		}
		pos.x += 1;
	}
}
