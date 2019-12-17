/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:28:09 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/16 22:02:41 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <string.h>
#include <math.h>
#include "libft.h"
#include "wolf3d.h"
#include "keystates.h"
#include "tile_inf.h"
#include "vec2.h"

int		wolf3d_play_events(t_ctx *ctx, SDL_Event event)
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

void	wolf3d_play_init(t_ctx *ctx)
{
	ctx->player = ctx->tile_map.player;
	ctx->player.fov = (90 / 360.) * M_PI;
	ctx->player.dist_to_proj = (ctx->window.size.width / 2)
		/ tan(ctx->player.fov / 2);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void	wolf3d_play_run(t_ctx *ctx)
{
	t_vec2d	old_pos;

	if (ctx->keystates & ESC_KEY)
		ctx->state = MAIN_MENU;
	else
	{
		old_pos = ctx->player.position;
		player_movement(ctx);
		check_collision_after_move(ctx, old_pos);
		minimap_reset_z_buffer(ctx);
		minimap_background(ctx);
		ft_memset(ctx->window.pixels, 0, ctx->window.size.width
			* ctx->window.size.height * sizeof(*ctx->window.pixels));
		player_view_raycast(ctx);
		draw_minimap_view(ctx);
	}
}

void	wolf3d_play_quit(t_ctx *ctx)
{
	size_t	total_size;
	size_t	idx;

	SDL_SetRelativeMouseMode(SDL_FALSE);
	total_size = ctx->tile_map.width * ctx->tile_map.height;
	idx = 0;
	while (idx < total_size)
	{
		ctx->tile_map.tiles[idx].type = NO_DATA;
		ft_memset(&ctx->tile_map.tiles[idx].data, 0, sizeof(t_tile_data));
		idx++;
	}
}
