/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:55:28 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/16 12:30:43 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include "libft.h"
#include "wolf3d.h"
#include "vec2.h"
#include "tile_inf.h"
#include "line_draw.h"
#include "error.h"

static int	minimap_plot_px(t_ctx *ctx, size_t idx, uint32_t color, int z_value)
{
	if (ctx->minimap.z_buffer[idx] < z_value)
	{
		ctx->minimap.pixels[idx] = color;
		ctx->minimap.z_buffer[idx] = z_value;
		return (1);
	}
	return (0);
}

static int	minimap_plot(t_ctx *ctx, t_vec2i pos)
{
	size_t	idx;
	t_vec2d	block_pos;

	idx = pos.y * ctx->minimap.size + pos.x;
	if (pos.x < MINIMAP_BORDER || pos.y < MINIMAP_BORDER
		|| pos.x >= (ctx->minimap.size - MINIMAP_BORDER)
		|| pos.y >= (ctx->minimap.size - MINIMAP_BORDER))
		return (minimap_plot_px(ctx, idx, MINIMAP_BORDER_COLOR, 100));
	block_pos = vec2d(pos.x, pos.y);
	block_pos = vec2d_mulf(block_pos, 1 / (double)ctx->minimap.size);
	block_pos = vec2d_sub(block_pos, vec2d(0.5, 0.5));
	block_pos = vec2d_mulf(block_pos, ctx->minimap.view_radius);
	block_pos = vec2d_add(block_pos, ctx->player.position);
	if (block_pos.x < 0 || block_pos.y < 0
		|| block_pos.x >= ctx->tile_map.width
		|| block_pos.y >= ctx->tile_map.height)
		return (minimap_plot_px(ctx, idx, MINIMAP_OUTSIDE_COLOR, 10));
	else if (ctx->tile_map.tiles[(int)block_pos.y * ctx->tile_map.width
			+ (int)block_pos.x] != TILE_EMPTY)
		return (minimap_plot_px(ctx, idx, MINIMAP_WALL_COLOR, 10));
	else if (fabs(block_pos.x - ctx->player.position.x) < PLAYER_HALF_SIZE
		&& fabs(block_pos.y - ctx->player.position.y) < PLAYER_HALF_SIZE)
		return (minimap_plot_px(ctx, idx, MINIMAP_PLAYER_COLOR, 1));
	else
		return (minimap_plot_px(ctx, idx, FLOOR_COLOR, -1));
}

t_error		minimap_setup(t_ctx *ctx)
{
	t_error	err;
	size_t	total_size;

	err = ERR_NOERROR;
	ctx->minimap.size = MINIMAP_SIZE * ctx->window.size.width;
	ctx->minimap.view_radius = ft_min(ft_min(ctx->tile_map.width
				, ctx->tile_map.height), MINIMAP_VIEW_RADIUS);
	total_size = ctx->minimap.size * ctx->minimap.size;
	ctx->minimap.pixels = (uint32_t *)malloc(total_size * sizeof(uint32_t));
	if (ctx->minimap.pixels == NULL)
		err = ERR_UNEXPECTED;
	else
	{
		ctx->minimap.z_buffer = (int *)malloc(total_size * sizeof(int));
		if (ctx->minimap.z_buffer == NULL)
			err = ERR_UNEXPECTED;
	}
	return (err);
}

void		minimap_destroy(t_minimap_inf *minimap)
{
	ft_memdel((void *)&minimap->pixels);
	ft_memdel((void *)&minimap->z_buffer);
}

void		minimap_reset_z_buffer(t_ctx *ctx)
{
	size_t	total_size;
	size_t	idx;

	total_size = ctx->minimap.size * ctx->minimap.size;
	idx = 0;
	while (idx < total_size)
	{
		ctx->minimap.z_buffer[idx] = INT_MIN;
		idx++;
	}
}

void		minimap_background(t_ctx *ctx)
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

void		minimap_ray(t_ctx *ctx, double length, double angle)
{
	t_line_ctx	line_ctx;
	double		ray_length;
	t_vec2i		start;
	t_vec2i		end;

	line_ctx.win_width = ctx->minimap.size;
	line_ctx.win_height = ctx->minimap.size;
	line_ctx.pixels = ctx->minimap.pixels;
	line_ctx.z_buffer = ctx->minimap.z_buffer;
	line_ctx.z_value = 0;
	ray_length = round(length / ctx->minimap.view_radius * ctx->minimap.size);
	start = vec2i(ctx->minimap.size / 2, ctx->minimap.size / 2);
	end = vec2i(start.x + cos(angle) * ray_length, start.y - sin(angle) * ray_length);
	draw_line(line_ctx, start, end, MINIMAP_RAY_COLOR);
}

void		draw_minimap_view(t_ctx *ctx)
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
