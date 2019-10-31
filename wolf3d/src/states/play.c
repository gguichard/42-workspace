/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:28:09 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/31 18:32:18 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include "libft.h"
#include "wolf3d.h"
#include "keystates.h"
#include "player.h"
#include "window.h"
#include "ray_inf.h"
#include "texture_inf.h"

static void	player_keys(t_ctx *ctx)
{
	if (ctx->keystates & ROTATE_LEFT_KEY)
		ctx->player.angle += M_PI / 80;
	if (ctx->keystates & ROTATE_RIGHT_KEY)
		ctx->player.angle -= M_PI / 80;
	if (ctx->keystates & (MOVE_FORWARD_KEY | MOVE_BACKWARD_KEY))
	{
		ctx->player.dir = vec2d_unit(vec2d(cos(ctx->player.angle)
					, -sin(ctx->player.angle)));
		if (ctx->keystates & MOVE_FORWARD_KEY)
			ctx->player.vel = vec2d_add(ctx->player.vel, vec2d(0.1, 0.1));
		if (ctx->keystates & MOVE_BACKWARD_KEY)
			ctx->player.vel = vec2d_sub(ctx->player.vel, vec2d(0.1, 0.1));
	}
}

static void	player_movement(t_ctx *ctx)
{
	if (vec2d_length2(ctx->player.vel) > 1)
		ctx->player.vel = vec2d_unit(ctx->player.vel);
	if (ctx->player.vel.x != 0.0)
		ctx->player.position.x += ctx->player.dir.x * ctx->player.vel.x * 0.2;
	if (ctx->player.vel.y != 0.0)
		ctx->player.position.y += ctx->player.dir.y * ctx->player.vel.y * 0.2;
	ctx->player.vel = vec2d_scalar(ctx->player.vel, 0.8);
}

static void	draw_ceil_floor(t_ctx *ctx, int x)
{
	int	half_height;
	int	y_index;

	half_height = ctx->window.size.height / 2;
	y_index = 0;
	while (y_index < half_height)
	{
		ctx->pixels[y_index * ctx->window.size.width + x] = 0x0000FF;
		ctx->pixels[(y_index + half_height) * ctx->window.size.width + x] =
			0x505050;
		y_index++;
	}
}

static void	draw_texture(t_ctx *ctx, int x, int height, t_ray_inf *ray_inf)
{
	int				wall_height;
	int				wall_offsets[2];
	int				y_index;
	t_texture_inf	*text_inf;
	t_vec2i			text_coord;

	wall_height = ft_min(height, ctx->window.size.height);
	wall_offsets[0] = ctx->window.size.height / 2 - wall_height / 2;
	wall_offsets[1] = height / 2 - wall_height / 2;
	y_index = 0;
	text_inf = &ctx->textures[ray_inf->direction];
	text_coord.x = (text_inf->width - 1) * ray_inf->position;
	while (y_index < wall_height)
	{
		text_coord.y = (text_inf->height - 1)
			* ((y_index + wall_offsets[1]) / (double)height);
		ctx->pixels[(y_index + wall_offsets[0]) * ctx->window.size.width + x] =
			text_inf->pixels[text_coord.y * text_inf->width + text_coord.x];
		y_index++;
	}
}

static void	draw_column(t_ctx *ctx, t_ray_inf *ray_inf, int x)
{
	int	height;

	draw_ceil_floor(ctx, x);
	if (ray_inf->length == 0.0)
		height = ctx->window.size.height;
	else
		height = round(ctx->player.dist_to_proj / ray_inf->length / 2) * 2;
	draw_texture(ctx, x, height, ray_inf);
}

static void	player_view_raycast(t_ctx *ctx)
{
	int			half_width;
	int			x;
	double		angle;
	t_ray_inf	ray_inf;

	half_width = ctx->window.size.width / 2;
	x = 0;
	while (x < ctx->window.size.width)
	{
		angle = ctx->player.angle - atan((x - half_width)
				/ ctx->player.dist_to_proj);
		ray_inf = launch_ray(ctx->player.position, angle, &ctx->tile_map);
		ray_inf.length *= cos(ctx->player.angle - angle);
		draw_column(ctx, &ray_inf, x);
		x++;
	}
}

void		wolf3d_play(t_ctx *ctx)
{
	if (ctx->keystates & ESC_KEY)
		ctx->state = QUIT;
	else
	{
		player_keys(ctx);
		player_movement(ctx);
		player_view_raycast(ctx);
	}
}
