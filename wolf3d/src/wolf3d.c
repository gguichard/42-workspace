/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:17:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/30 16:18:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <SDL.h>
#include "libft.h"
#include "wolf3d.h"
#include "window.h"
#include "error.h"

t_statefn		*g_states[STATE_LAST];
t_state_evtfn	*g_states_evt[STATE_LAST];

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
			ctx->state = MAIN_MENU;
			g_states[MAIN_MENU] = wolf3d_main_menu;
			g_states[PLAYING] = wolf3d_play;
			g_states_evt[PLAYING] = wolf3d_play_events;
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
	t_statefn	*fn;
	int			dumb;

	while (ctx->state != QUIT)
	{
		wolf3d_events(ctx);
		if (SDL_LockTexture(ctx->window.texture, NULL
			, (void **)&ctx->window.pixels, &dumb) < 0)
			break ;
		fn = g_states[ctx->state];
		if (fn != NULL)
			fn(ctx);
		SDL_RenderCopy(ctx->window.renderer, ctx->window.texture, NULL, NULL);
		SDL_UnlockTexture(ctx->window.texture);
		SDL_RenderPresent(ctx->window.renderer);
	}
}
