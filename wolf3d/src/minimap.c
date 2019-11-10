/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:55:28 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/10 15:21:42 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "libft.h"
#include "wolf3d.h"
#include "vec2.h"
#include "tile_inf.h"
#include "line_draw.h"
#include "error.h"

static uint32_t	minimap_color(t_ctx *ctx, t_vec2i pos)
{
	t_vec2d	block_pos;

	if (pos.x < MINIMAP_BORDER || pos.y < MINIMAP_BORDER
		|| pos.x >= (ctx->minimap.size - MINIMAP_BORDER)
		|| pos.y >= (ctx->minimap.size - MINIMAP_BORDER))
		return (MINIMAP_BORDER_COLOR);
	block_pos = vec2d(pos.x, pos.y);
	block_pos = vec2d_mulf(block_pos, 1 / (double)ctx->minimap.size);
	block_pos = vec2d_sub(block_pos, vec2d(0.5, 0.5));
	block_pos = vec2d_mulf(block_pos, ctx->minimap.view_radius);
	block_pos = vec2d_add(block_pos, ctx->player.position);
	if (block_pos.x < 0 || block_pos.y < 0
		|| block_pos.x >= ctx->tile_map.width
		|| block_pos.y >= ctx->tile_map.height)
		return (MINIMAP_OUTSIDE_COLOR);
	else if (ctx->tile_map.tiles[(int)block_pos.y * ctx->tile_map.width
			+ (int)block_pos.x] != TILE_EMPTY)
		return (MINIMAP_WALL_COLOR);
	else if (fabs(block_pos.x - ctx->player.position.x) < PLAYER_HALF_SIZE
		&& fabs(block_pos.y - ctx->player.position.y) < PLAYER_HALF_SIZE)
		return (MINIMAP_PLAYER_COLOR);
	else
		return (FLOOR_COLOR);
}

t_error			minimap_setup(t_ctx *ctx)
{
	t_error	err;

	err = ERR_NOERROR;
	ctx->minimap.size = MINIMAP_SIZE * ctx->window.size.width;
	ctx->minimap.view_radius = ft_min(ft_min(ctx->tile_map.width
				, ctx->tile_map.height), MINIMAP_VIEW_RADIUS);
	ctx->minimap.pixels = (uint32_t *)malloc(
				ctx->minimap.size * ctx->minimap.size * sizeof(uint32_t));
	if (ctx->minimap.pixels == NULL)
		err = ERR_UNEXPECTED;
	return (err);
}

void			minimap_destroy(t_minimap_inf *minimap)
{
	ft_memdel((void *)&minimap->pixels);
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
			ctx->minimap.pixels[pos.y * ctx->minimap.size + pos.x] =
				minimap_color(ctx, pos);
			pos.y += 1;
		}
		pos.x += 1;
	}
}

void			minimap_ray(t_ctx *ctx, double length, double angle)
{
	t_line_ctx	line_ctx;
	t_vec2i		start;
	t_vec2i		end;

	line_ctx.win_width = ctx->minimap.size;
	line_ctx.win_height = ctx->minimap.size;
	line_ctx.pixels = ctx->minimap.pixels;
	length = length / ctx->minimap.view_radius * ctx->minimap.size;
	start = vec2i(ctx->minimap.size / 2, ctx->minimap.size / 2);
	end = vec2i(start.x + cos(angle) * length, start.y - sin(angle) * length);
	draw_line(line_ctx, start, end, MINIMAP_PLAYER_COLOR);
}

void			draw_minimap_view(t_ctx *ctx)
{
	int	y;

	y = 0;
	while (y < ctx->minimap.size)
	{
		ft_memcpy(&ctx->window.pixels[(y + MINIMAP_OFFSET_Y)
				* ctx->window.size.width + MINIMAP_OFFSET_X]
			, ctx->minimap.pixels + y * ctx->minimap.size
			, ctx->minimap.size * sizeof(uint32_t));
		y++;
	}
}
