/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:28:09 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/20 17:24:19 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <math.h>
#include <stdint.h>
#include "libft.h"
#include "wolf3d.h"
#include "keystates.h"
#include "player.h"
#include "window.h"
#include "ray_inf.h"
#include "tile_inf.h"
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

static void	player_movement(t_ctx *ctx)
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

static void	draw_ceil_floor(t_ctx *ctx, int x)
{
	int	half_height;
	int	y_index;

	half_height = ctx->window.size.height / 2;
	y_index = 0;
	while (y_index < half_height)
	{
		ctx->window.pixels[y_index * ctx->window.size.width + x] = CEIL_COLOR;
		ctx->window.pixels[(y_index + half_height)
			* ctx->window.size.width + x] = FLOOR_COLOR;
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
		ctx->window.pixels[(y_index + wall_offsets[0])
			* ctx->window.size.width + x] = text_inf->pixels[text_coord.y
					* text_inf->width + text_coord.x];
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

static int	search_portal(t_ctx *ctx, t_portal_type type)
{
	size_t	total_size;
	size_t	idx;

	total_size = ctx->tile_map.width * ctx->tile_map.height;
	idx = 0;
	while (idx < total_size)
	{
		if (ctx->tile_map.tiles[idx].type == PORTAL_DATA
			&& ctx->tile_map.tiles[idx].data.portal.type == type)
			return (idx);
		idx++;
	}
	return (-1);
}

static void	create_portal(t_ctx *ctx, t_portal_type type)
{
	t_ray_inf	ray_inf;

	ray_inf = launch_ray(ctx->player.position, ctx->player.angle
		, &ctx->tile_map);
	if (ray_inf.tile != NULL)
	{
		ray_inf.tile->type = PORTAL_DATA;
		ray_inf.tile->data.portal.type = type;
		ray_inf.tile->data.portal.dir = ray_inf.direction;
		ray_inf.tile->data.portal.target = search_portal(ctx
			, (type == FIRST_PORTAL) ? SECOND_PORTAL : FIRST_PORTAL);
		if (ray_inf.tile->data.portal.target != -1)
			ctx->tile_map.tiles[ray_inf.tile->data.portal.target]
				.data.portal.target = ray_inf.tile->pos.y * ctx->tile_map.width
					+ ray_inf.tile->pos.x;
	}
}

int			wolf3d_play_events(t_ctx *ctx, SDL_Event event)
{
	double	x_move;

	if (event.type == SDL_MOUSEMOTION)
	{
		x_move = event.motion.xrel;
		ctx->player.angle -= x_move * (M_PI / 1000);
		return (1);
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
			create_portal(ctx, FIRST_PORTAL);
		else if (event.button.button == SDL_BUTTON_RIGHT)
			create_portal(ctx, SECOND_PORTAL);
		return (1);
	}
	return (0);
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
		minimap_reset_z_buffer(ctx);
		minimap_background(ctx);
		player_view_raycast(ctx);
		draw_minimap_view(ctx);
	}
}
