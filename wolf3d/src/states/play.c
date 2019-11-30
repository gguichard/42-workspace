/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:28:09 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/30 15:10:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <math.h>
#include "wolf3d.h"
#include "keystates.h"
#include "ray_inf.h"
#include "tile_inf.h"
#include "vec2.h"

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
	int			prev_portal;

	ray_inf = launch_ray(ctx->player.position, ctx->player.angle
		, &ctx->tile_map);
	if (ray_inf.tile != NULL)
		ray_inf = launch_portal_ray(&ray_inf, &ctx->tile_map);
	if (ray_inf.tile != NULL)
	{
		prev_portal = search_portal(ctx, type);
		if (prev_portal != -1)
			ctx->tile_map.tiles[prev_portal].type = NO_DATA;
		ray_inf.tile->type = PORTAL_DATA;
		ray_inf.tile->data.portal.type = type;
		ray_inf.tile->data.portal.dir = ray_inf.direction;
		ray_inf.tile->data.portal.target = search_portal(ctx
			, (type == ENTRY_PORTAL) ? EXIT_PORTAL : ENTRY_PORTAL);
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
			create_portal(ctx, ENTRY_PORTAL);
		else if (event.button.button == SDL_BUTTON_RIGHT)
			create_portal(ctx, EXIT_PORTAL);
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
