/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:56:00 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/03 12:20:03 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf3d.h"
#include "player.h"
#include "keystates.h"
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
			acc = vec2d_mulf(vec2d_unit(acc), PLAYER_STRAFE_ACCEL);
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
			acc = vec2d_mulf(vec2d_unit(acc), PLAYER_ACCEL);
			ctx->player.velocity = vec2d_add(ctx->player.velocity, acc);
		}
	}
}

void		player_movement(t_ctx *ctx)
{
	t_vec2d	old_velocity;
	double	velocity_speed;

	old_velocity = ctx->player.velocity;
	handle_player_keys(ctx);
	if (old_velocity.x == ctx->player.velocity.x
		&& old_velocity.y == ctx->player.velocity.y)
	{
		ctx->player.velocity = vec2d_mulf(ctx->player.velocity
			, PLAYER_VELOCITY_DECREASE);
	}
	velocity_speed = sqrt(vec2d_length2(ctx->player.velocity));
	if (velocity_speed > PLAYER_MAX_SPEED)
	{
		ctx->player.velocity = vec2d_mulf(vec2d_unit(ctx->player.velocity)
			, PLAYER_MAX_SPEED);
	}
	ctx->player.position = vec2d_add(ctx->player.position
		, ctx->player.velocity);
}
