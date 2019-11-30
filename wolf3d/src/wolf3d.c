/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:17:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/30 19:00:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <SDL.h>
#include "libft.h"
#include "wolf3d.h"
#include "window.h"
#include "state.h"
#include "error.h"

static t_error	load_textures(t_ctx *ctx)
{
	static const char	*files[] = {
		"textures/north.bmp",
		"textures/west.bmp",
		"textures/south.bmp",
		"textures/east.bmp",
		"textures/portal_entry.bmp",
		"textures/portal_exit.bmp",
	};
	t_error				err;
	size_t				idx;

	err = ERR_NOERROR;
	idx = 0;
	while (idx < (sizeof(files) / sizeof(files[0])))
	{
		err = load_texture(files[idx], &ctx->textures[idx]);
		if (err != ERR_NOERROR)
			break ;
		idx++;
	}
	return (err);
}

static void		setup_states(t_ctx *ctx)
{
	t_state_inf	*states;

	states = ctx->states;
	states[MAIN_MENU].run_fn = wolf3d_main_menu;
	states[PLAYING].init_fn = wolf3d_play_init;
	states[PLAYING].run_fn = wolf3d_play_run;
	states[PLAYING].evt_fn = wolf3d_play_events;
}

t_error			wolf3d_init(t_ctx *ctx, const char *mapfile)
{
	t_error	err;

	ft_memset(ctx, 0, sizeof(t_ctx));
	ctx->tile_map = load_mapfile(mapfile, &err);
	if (err == ERR_NOERROR)
		err = load_textures(ctx);
	if (err == ERR_NOERROR)
	{
		ctx->window.title = "Wolf3D";
		ctx->window.size.width = 1280;
		ctx->window.size.height = 960;
		err = window_create(&ctx->window);
		if (err == ERR_NOERROR)
			err = minimap_setup(ctx);
		if (err == ERR_NOERROR)
		{
			setup_states(ctx);
			ctx->state = MAIN_MENU;
			wolf3d_run(ctx);
		}
	}
	return (err);
}

void			wolf3d_clean(t_ctx *ctx)
{
	size_t	idx;

	window_destroy(&ctx->window);
	minimap_destroy(&ctx->minimap);
	ft_memdel((void **)&ctx->tile_map.tiles);
	idx = 0;
	while (idx < (sizeof(ctx->textures) / sizeof(ctx->textures[0])))
	{
		ft_memdel((void **)&ctx->textures[idx].pixels);
		idx++;
	}
}

void			wolf3d_run(t_ctx *ctx)
{
	t_state_type	old_state;
	int				dumb;

	old_state = STATE_LAST;
	while (ctx->state != QUIT)
	{
		wolf3d_events(ctx);
		if (SDL_LockTexture(ctx->window.texture, NULL
			, (void **)&ctx->window.pixels, &dumb) < 0)
			break ;
		if (ctx->state != old_state)
		{
			if (old_state != STATE_LAST
				&& ctx->states[old_state].quit_fn != NULL)
				ctx->states[old_state].quit_fn(ctx);
			if (ctx->states[ctx->state].init_fn != NULL)
				ctx->states[ctx->state].init_fn(ctx);
			old_state = ctx->state;
		}
		if (ctx->states[ctx->state].run_fn != NULL)
			ctx->states[ctx->state].run_fn(ctx);
		SDL_RenderCopy(ctx->window.renderer, ctx->window.texture, NULL, NULL);
		SDL_UnlockTexture(ctx->window.texture);
		SDL_RenderPresent(ctx->window.renderer);
	}
}
