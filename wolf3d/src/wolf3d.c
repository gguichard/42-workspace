/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:17:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/27 23:17:00 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "libft.h"
#include "wolf3d.h"
#include "keystates.h"
#include "window.h"
#include "error.h"

static t_statefn	*g_states[STATE_LAST];
static t_key		g_keys[] = {
	{SDLK_ESCAPE, ESC_KEY},
	{SDLK_RETURN, ENTER_KEY},
	{SDLK_UP, MOVE_FORWARD_KEY},
	{SDLK_DOWN, MOVE_BACKWARD_KEY},
	{SDLK_LEFT, STRAFE_LEFT_KEY},
	{SDLK_RIGHT, STRAFE_RIGHT_KEY}
};

static void	wolf3d_events(t_ctx *ctx)
{
	SDL_Event	event;
	size_t		idx;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			ctx->state = QUIT;
		else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			idx = 0;
			while (idx < (sizeof(g_keys) / sizeof(g_keys[0])))
			{
				if (g_keys[idx].keycode == event.key.keysym.sym)
				{
					if (event.type == SDL_KEYDOWN)
						ctx->keystates |= g_keys[idx].bitmask;
					else
						ctx->keystates &= ~g_keys[idx].bitmask;
					break ;
				}
				idx++;
			}
		}
	}
}

t_error		wolf3d_init(const char *mapfile)
{
	t_ctx	ctx;
	t_error	err;

	ctx.tile_map = load_mapfile(mapfile, &err);
	if (err == ERR_NOERROR)
	{
		ft_memset(&ctx, 0, sizeof(t_ctx));
		ctx.window.title = "Wolf3d";
		ctx.window.size.width = 800;
		ctx.window.size.height = 600;
		err = window_create(&ctx.window);
		if (err == ERR_NOERROR)
		{
			ctx.state = MAIN_MENU;
			g_states[MAIN_MENU] = wolf3d_main_menu;
			g_states[PLAYING] = wolf3d_play;
			wolf3d_run(&ctx);
		}
	}
	return (err);
}

void		wolf3d_run(t_ctx *ctx)
{
	t_statefn	*fn;
	int			dumb;

	while (ctx->state != QUIT)
	{
		if (SDL_LockTexture(ctx->window.texture, NULL
			, (void **)&ctx->pixels, &dumb) < 0)
			break ;
		fn = g_states[ctx->state];
		if (fn != NULL)
			fn(ctx);
		SDL_UnlockTexture(ctx->window.texture);
		SDL_RenderCopy(ctx->window.renderer, ctx->window.texture, NULL, NULL);
		SDL_RenderPresent(ctx->window.renderer);
		wolf3d_events(ctx);
	}
	ft_memdel((void **)ctx->tile_map.tiles);
}
