/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 22:49:22 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/04 09:11:19 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "wolf3d.h"
#include "thread_inf.h"
#include "column_inf.h"
#include "tile_inf.h"
#include "texture_inf.h"
#include "ray_inf.h"

void		setup_draw_ctx(t_ctx *ctx, t_ray_inf *ray_inf
	, t_draw_ctx *draw_ctx)
{
	if (ray_inf->length == 0.0)
		draw_ctx->wall_height = ctx->window.size.height;
	else
	{
		draw_ctx->wall_height = ctx->player.dist_to_proj
			/ (ray_inf->length * ray_inf->fisheye_angle);
	}
	draw_ctx->wall_height = round(draw_ctx->wall_height * 4) / 2;
	draw_ctx->wall_screen_height = ft_min(draw_ctx->wall_height
		, ctx->window.size.height);
	draw_ctx->wall_top = draw_ctx->wall_height / 2
		- draw_ctx->wall_screen_height / 2;
	draw_ctx->wall_screen_top = ctx->window.size.height / 2
		- draw_ctx->wall_screen_height / 2;
}

static void	reset_portal_z_buffer(t_column_inf *column_inf)
{
	size_t	y;

	y = 0;
	while (y < (sizeof(column_inf->z_buffer) / sizeof(column_inf->z_buffer[0])))
	{
		if (column_inf->z_buffer[y] != 100)
			column_inf->z_buffer[y] = 0;
		y++;
	}
}

static void	draw_portal(t_ctx *ctx, t_column_inf *column_inf
	, t_ray_inf *hit_inf)
{
	t_texture_inf	*text_inf;
	t_ray_inf		ray_inf;

	if (hit_inf->tile->data.portal.type == ENTRY_PORTAL)
		text_inf = &ctx->textures[TEXTURE_PORTAL_ENTRY];
	else
		text_inf = &ctx->textures[TEXTURE_PORTAL_EXIT];
	if (!column_inf->use_z_buffer)
		ft_memset(column_inf->z_buffer, 0xff, sizeof(column_inf->z_buffer));
	else
		reset_portal_z_buffer(column_inf);
	column_inf->depth -= 1;
	column_inf->use_z_buffer = 1;
	draw_texture(ctx, column_inf, hit_inf, text_inf);
	if (column_inf->depth > 0 && hit_inf->tile->data.portal.target != NULL)
	{
		ray_inf = launch_portal_ray(hit_inf, &ctx->tile_map);
		draw_column(ctx, column_inf, &ray_inf);
		if (ray_inf.tile != NULL
			&& ray_inf.tile->type == PORTAL_DATA
			&& ray_inf.tile->data.portal.dir == ray_inf.direction)
			draw_portal(ctx, column_inf, &ray_inf);
	}
	column_inf->use_z_buffer = 0;
}

void		player_view_thread(t_thread_inf *thread_inf)
{
	t_ctx			*ctx;
	int				half_width;
	double			angle;
	t_ray_inf		hit_inf;
	t_column_inf	column_inf;

	ctx = (t_ctx *)thread_inf->data;
	half_width = ctx->window.size.width / 2;
	column_inf.x = thread_inf->x_start;
	while (column_inf.x < ctx->window.size.width)
	{
		column_inf.use_z_buffer = 0;
		column_inf.depth = FOG_DIST + 1;
		angle = ctx->player.angle - atan((column_inf.x - half_width)
				/ ctx->player.dist_to_proj);
		hit_inf = launch_ray(ctx->player.position, angle, &ctx->tile_map);
		hit_inf.fisheye_angle = cos(ctx->player.angle - angle);
		minimap_ray(ctx, hit_inf.length, angle);
		draw_column(ctx, &column_inf, &hit_inf);
		if (hit_inf.tile != NULL && hit_inf.tile->type == PORTAL_DATA
			&& hit_inf.tile->data.portal.dir == hit_inf.direction
			&& hit_inf.length < FOG_DIST)
			draw_portal(ctx, &column_inf, &hit_inf);
		column_inf.x += THREADS_COUNT;
	}
}
