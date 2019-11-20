/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 22:49:22 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/20 22:52:19 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <math.h>
#include "libft.h"
#include "wolf3d.h"
#include "texture_inf.h"
#include "ray_inf.h"
#include "vec2.h"
#include "utils.h"

static uint32_t	darker_color(uint32_t color, double percent)
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
	return ((r << 16) | (g << 8) | b);
}

static void		draw_ceil_floor(t_ctx *ctx, int x)
{
	int		half_height;
	int		y_index;
	double	darker;

	half_height = ctx->window.size.height / 2;
	y_index = 0;
	while (y_index < half_height)
	{
		darker = y_index / (double)half_height;
		ctx->window.pixels[y_index
			* ctx->window.size.width + x] = darker_color(CEIL_COLOR, darker);
		ctx->window.pixels[(ctx->window.size.height - y_index - 1)
			* ctx->window.size.width + x] = darker_color(FLOOR_COLOR, darker);
		y_index++;
	}
}

static void		draw_texture(t_ctx *ctx, int x, int height, t_ray_inf *ray_inf)
{
	int				wall_height;
	int				wall_offsets[2];
	int				y_index;
	t_texture_inf	*text_inf;
	t_vec2i			text_coord;
	double			darker;

	wall_height = ft_min(height, ctx->window.size.height);
	wall_offsets[0] = ctx->window.size.height / 2 - wall_height / 2;
	wall_offsets[1] = height / 2 - wall_height / 2;
	y_index = 0;
	text_inf = &ctx->textures[ray_inf->direction];
	text_coord.x = (text_inf->width - 1) * ray_inf->position;
	darker = clamp(ray_inf->length / 15, 0, 1);
	while (y_index < wall_height)
	{
		text_coord.y = (text_inf->height - 1)
			* ((y_index + wall_offsets[1]) / (double)height);
		ctx->window.pixels[(y_index + wall_offsets[0])
			* ctx->window.size.width + x] = darker_color(
				text_inf->pixels[text_coord.y
					* text_inf->width + text_coord.x], darker);
		y_index++;
	}
}

static void		draw_column(t_ctx *ctx, t_ray_inf *ray_inf, int x)
{
	int	height;

	draw_ceil_floor(ctx, x);
	if (ray_inf->length == 0.0)
		height = ctx->window.size.height;
	else
		height = round(ctx->player.dist_to_proj / ray_inf->length / 2) * 2;
	draw_texture(ctx, x, height, ray_inf);
}

void			player_view_raycast(t_ctx *ctx)
{
	int			half_width;
	int			x;
	double		angle;
	t_ray_inf	hit_inf;
	t_ray_inf	ray_inf;

	half_width = ctx->window.size.width / 2;
	x = 0;
	while (x < ctx->window.size.width)
	{
		angle = ctx->player.angle - atan((x - half_width)
				/ ctx->player.dist_to_proj);
		hit_inf = launch_ray(ctx->player.position, angle, &ctx->tile_map);
		minimap_ray(ctx, hit_inf.length, angle);
		ray_inf = launch_portal_ray(hit_inf, angle, &ctx->tile_map, 100);
		ray_inf.length *= cos(ctx->player.angle - angle);
		draw_column(ctx, &ray_inf, x);
		x++;
	}
}
