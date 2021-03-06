/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 13:19:55 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/17 17:45:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include "wolf3d.h"
#include "column_inf.h"
#include "tile_inf.h"
#include "ray_inf.h"
#include "vec2.h"
#include "utils.h"

inline static uint32_t	darker_color(uint32_t color, double percent)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = (color >> 16) & 0xff;
	g = (color >> 8) & 0xff;
	b = color & 0xff;
	r *= (1 - percent);
	g *= (1 - percent);
	b *= (1 - percent);
	return ((color & ALPHA_CHANNEL) | (r << 16) | (g << 8) | b);
}

static void				draw_texture(t_ctx *ctx, t_column_inf *column_inf
	, t_ray_inf *ray_inf, t_texture_inf *text_inf)
{
	t_draw_ctx	draw_ctx;
	t_vec2i		text_coord;
	double		darker;
	int			y_index;
	uint32_t	color;

	setup_draw_ctx(ctx, ray_inf, column_inf->fisheye_angle, &draw_ctx);
	text_coord.x = (text_inf->width - 1) * ray_inf->position;
	darker = clamp(ray_inf->length / FOG_DIST, 0, 1);
	y_index = 0;
	while (y_index < draw_ctx.wall_screen_height)
	{
		text_coord.y = (text_inf->height - 1)
			* ((y_index + draw_ctx.wall_top) / (double)draw_ctx.wall_height);
		color = text_inf->pixels[text_coord.y * text_inf->width + text_coord.x];
		if (color == 0xff000000
			&& (text_inf == &ctx->textures[TEXTURE_PORTAL_ENTRY]
				|| text_inf == &ctx->textures[TEXTURE_PORTAL_EXIT]))
			column_inf->pixels[y_index + draw_ctx.wall_screen_top] = 0x0;
		else if ((color & ALPHA_CHANNEL) == ALPHA_CHANNEL)
			column_inf->pixels[y_index + draw_ctx.wall_screen_top] =
				darker_color(color, darker);
		y_index++;
	}
}

static void				draw_portal(t_ctx *ctx, t_column_inf *column_inf
	, t_ray_inf *hit_inf)
{
	t_texture_inf	*text_inf;

	if (hit_inf->tile->data.portal.type == ENTRY_PORTAL)
		text_inf = &ctx->textures[TEXTURE_PORTAL_ENTRY];
	else
		text_inf = &ctx->textures[TEXTURE_PORTAL_EXIT];
	draw_texture(ctx, column_inf, hit_inf, text_inf);
}

static void				column_to_window(t_ctx *ctx, t_column_inf *column_inf)
{
	int	y_index;

	y_index = 0;
	while (y_index < ctx->window.size.height)
	{
		if ((column_inf->pixels[y_index] & ALPHA_CHANNEL) == ALPHA_CHANNEL)
			ctx->window.pixels[y_index
				* ctx->window.size.width + column_inf->x] =
				column_inf->pixels[y_index];
		y_index++;
	}
}

void					draw_column(t_ctx *ctx, t_column_inf *column_inf
	, t_ray_inf *ray_inf)
{
	int		half_height;
	int		y_index;
	double	darker;

	ft_memset(column_inf->pixels, 0, sizeof(column_inf->pixels));
	half_height = ctx->window.size.height / 2;
	y_index = 0;
	while (y_index < half_height)
	{
		darker = y_index / (double)half_height;
		column_inf->pixels[y_index] = darker_color(CEIL_COLOR, darker);
		column_inf->pixels[ctx->window.size.height - y_index - 1] =
			darker_color(FLOOR_COLOR, darker);
		y_index++;
	}
	draw_texture(ctx, column_inf, ray_inf, &ctx->textures[ray_inf->direction]);
	if (ray_inf->tile->type == PORTAL_DATA
		&& ray_inf->tile->data.portal.dir == ray_inf->direction)
		draw_portal(ctx, column_inf, ray_inf);
	column_to_window(ctx, column_inf);
}
