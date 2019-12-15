/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 13:17:42 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/05 14:53:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "libft.h"
#include "wolf3d.h"
#include "minimap_inf.h"
#include "line_draw.h"
#include "vec2.h"
#include "error.h"

t_error	minimap_setup(t_ctx *ctx)
{
	t_error	err;
	int		min_size_radius;
	size_t	total_size;

	err = ERR_NOERROR;
	ctx->minimap.size = MINIMAP_SIZE * ctx->window.size.width;
	min_size_radius = ft_min(ctx->tile_map.width, ctx->tile_map.height);
	ctx->minimap.view_radius = ft_min(min_size_radius, MINIMAP_VIEW_RADIUS);
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

void	minimap_destroy(t_minimap_inf *minimap)
{
	ft_memdel((void *)&minimap->pixels);
	ft_memdel((void *)&minimap->z_buffer);
}

void	minimap_reset_z_buffer(t_ctx *ctx)
{
	size_t	total_size;

	total_size = ctx->minimap.size * ctx->minimap.size;
	ft_memset(ctx->minimap.z_buffer, 0xff, total_size
		* sizeof(*ctx->minimap.z_buffer));
}

void	minimap_ray(t_ctx *ctx, double length, double angle)
{
	t_line_ctx	line_ctx;
	double		ray_length;
	t_vec2i		start;
	t_vec2i		end;

	line_ctx.win_width = ctx->minimap.size;
	line_ctx.win_height = ctx->minimap.size;
	line_ctx.pixels = ctx->minimap.pixels;
	line_ctx.z_buffer = ctx->minimap.z_buffer;
	line_ctx.z_value = 5;
	ray_length = ceil(length / ctx->minimap.view_radius * ctx->minimap.size);
	start = vec2i(ctx->minimap.size / 2, ctx->minimap.size / 2);
	end = vec2i(start.x + cos(angle) * ray_length
			, start.y - sin(angle) * ray_length);
	draw_line(line_ctx, start, end, MINIMAP_RAY_COLOR);
}

void	draw_minimap_view(t_ctx *ctx)
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
