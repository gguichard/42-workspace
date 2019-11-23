/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 22:49:22 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/25 22:15:51 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "wolf3d.h"
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

static void	reset_z_buffer(t_ctx *ctx, int x)
{
	int	y;

	y = 0;
	while (y < ctx->window.size.height)
	{
		ctx->z_buffer[y * ctx->window.size.width + x] = 0;
		y++;
	}
}

static void	reset_portal_z_buffer(t_ctx *ctx, int x)
{
	int	y;

	y = 0;
	while (y < ctx->window.size.height)
	{
		if (ctx->z_buffer[y * ctx->window.size.width + x] != 100)
			ctx->z_buffer[y * ctx->window.size.width + x] = 0;
		y++;
	}
}

static void	draw_portal(t_ctx *ctx, t_ray_inf *hit_inf, int x, double angle)
{
	t_texture_inf	*text_inf;
	t_ray_inf		ray_inf;

	if (hit_inf->tile->data.portal.type == ENTRY_PORTAL)
		text_inf = &ctx->textures[PORTAL_ENTRY_TEXTURE];
	else
		text_inf = &ctx->textures[PORTAL_EXIT_TEXTURE];
	if (!ctx->use_z_buffer)
		reset_z_buffer(ctx, x);
	else
		reset_portal_z_buffer(ctx, x);
	ctx->depth -= 1;
	ctx->use_z_buffer = 1;
	draw_texture(ctx, hit_inf, text_inf, x);
	if (ctx->depth > 0 && hit_inf->tile->data.portal.target != -1)
	{
		ray_inf = launch_portal_ray(hit_inf, angle, &ctx->tile_map);
		draw_column(ctx, &ray_inf, x);
		if (ray_inf.tile != NULL
			&& ray_inf.tile->type == PORTAL_DATA
			&& ray_inf.tile->data.portal.dir == ray_inf.direction)
			draw_portal(ctx, &ray_inf, x, angle);
	}
	ctx->use_z_buffer = 0;
}

void		player_view_raycast(t_ctx *ctx)
{
	int			half_width;
	int			x;
	double		angle;
	t_ray_inf	hit_inf;

	half_width = ctx->window.size.width / 2;
	x = 0;
	while (x < ctx->window.size.width)
	{
		angle = ctx->player.angle - atan((x - half_width)
				/ ctx->player.dist_to_proj);
		hit_inf = launch_ray(ctx->player.position, angle, &ctx->tile_map);
		hit_inf.fisheye_angle = cos(ctx->player.angle - angle);
		minimap_ray(ctx, hit_inf.length, angle);
		draw_column(ctx, &hit_inf, x);
		if (hit_inf.tile != NULL
			&& hit_inf.tile->type == PORTAL_DATA
			&& hit_inf.tile->data.portal.dir == hit_inf.direction)
		{
			ctx->depth = FOG_DIST;
			draw_portal(ctx, &hit_inf, x, angle);
		}
		x++;
	}
}
