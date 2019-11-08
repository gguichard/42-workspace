/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:28:09 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/08 15:26:36 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include "libft.h"
#include "wolf3d.h"
#include "keystates.h"
#include "player.h"
#include "window.h"
#include "minimap.h"
#include "ray_inf.h"
#include "texture_inf.h"
#include "vec2.h"

static void	handle_player_strafe_keys(t_ctx *ctx)
{
	t_vec2d	acc;
	double	angle;
	t_vec2d	dir;

	if (ctx->keystates & (STRAFE_LEFT_KEY | STRAFE_RIGHT_KEY))
	{
		acc = vec2d(0, 0);
		angle = ctx->player.angle + M_PI / 2;
		dir = vec2d(cos(angle), -sin(angle));
		if (ctx->keystates & STRAFE_LEFT_KEY)
			acc = vec2d_add(acc, dir);
		if (ctx->keystates & STRAFE_RIGHT_KEY)
			acc = vec2d_sub(acc, dir);
		if (acc.x != 0.0 || acc.y != 0.0)
		{
			acc = vec2d_scalar(vec2d_unit(acc), PLAYER_STRAFE_ACCEL);
			ctx->player.velocity = vec2d_add(ctx->player.velocity, acc);
		}
	}
}

static void	handle_player_keys(t_ctx *ctx)
{
	t_vec2d	acc;
	t_vec2d	dir;

	if (ctx->keystates & ROTATE_LEFT_KEY)
		ctx->player.angle += M_PI / 80;
	if (ctx->keystates & ROTATE_RIGHT_KEY)
		ctx->player.angle -= M_PI / 80;
	handle_player_strafe_keys(ctx);
	if (ctx->keystates & (MOVE_FORWARD_KEY | MOVE_BACKWARD_KEY))
	{
		acc = vec2d(0, 0);
		dir = vec2d(cos(ctx->player.angle), -sin(ctx->player.angle));
		if (ctx->keystates & MOVE_FORWARD_KEY)
			acc = vec2d_add(acc, dir);
		if (ctx->keystates & MOVE_BACKWARD_KEY)
			acc = vec2d_sub(acc, dir);
		if (acc.x != 0.0 || acc.y != 0.0)
		{
			acc = vec2d_scalar(vec2d_unit(acc), PLAYER_ACCEL);
			ctx->player.velocity = vec2d_add(ctx->player.velocity, acc);
		}
	}
}

static void	player_movement(t_ctx *ctx)
{
	t_vec2d	old_velocity;
	double	velocity_speed;

	old_velocity = ctx->player.velocity;
	handle_player_keys(ctx);
	if (old_velocity.x == ctx->player.velocity.x
		&& old_velocity.y == ctx->player.velocity.y)
	{
		ctx->player.velocity = vec2d_scalar(ctx->player.velocity
			, PLAYER_VELOCITY_DECREASE);
	}
	velocity_speed = sqrt(vec2d_length2(ctx->player.velocity));
	if (velocity_speed > PLAYER_MAX_SPEED)
	{
		ctx->player.velocity = vec2d_scalar(vec2d_unit(ctx->player.velocity)
			, PLAYER_MAX_SPEED);
	}
	ctx->player.position = vec2d_add(ctx->player.position
		, ctx->player.velocity);
}

static void	draw_ceil_floor(t_ctx *ctx, int x)
{
	int	half_height;
	int	y_index;

	half_height = ctx->window.size.height / 2;
	y_index = 0;
	while (y_index < half_height)
	{
		ctx->pixels[y_index * ctx->window.size.width + x] = 0x427ef5;
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
	t_vec2d	old_pos;

	if (ctx->keystates & ESC_KEY)
		ctx->state = QUIT;
	else
	{
		old_pos = ctx->player.position;
		player_movement(ctx);
		check_collision_after_move(ctx, old_pos);
		player_view_raycast(ctx);
		draw_map_view(ctx);
	}
}
