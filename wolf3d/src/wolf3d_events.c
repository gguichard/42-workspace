/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:22:59 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/04 09:22:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <SDL.h>
#include "wolf3d.h"
#include "keystates.h"

static t_key	g_keys[] = {
	{SDLK_ESCAPE, ESC_KEY},
	{SDLK_RETURN, ENTER_KEY},
	{SDLK_UP, MOVE_FORWARD_KEY},
	{SDLK_DOWN, MOVE_BACKWARD_KEY},
	{SDLK_w, MOVE_FORWARD_KEY},
	{SDLK_s, MOVE_BACKWARD_KEY},
	{SDLK_a, STRAFE_LEFT_KEY},
	{SDLK_d, STRAFE_RIGHT_KEY},
	{SDLK_LEFT, ROTATE_LEFT_KEY},
	{SDLK_RIGHT, ROTATE_RIGHT_KEY}
};

static void	wolf3d_keys(t_ctx *ctx, SDL_Event *event)
{
	size_t	idx;

	idx = 0;
	while (idx < (sizeof(g_keys) / sizeof(g_keys[0])))
	{
		if (g_keys[idx].keycode == event->key.keysym.sym)
		{
			if (event->type == SDL_KEYDOWN)
				ctx->keystates |= g_keys[idx].bitmask;
			else
				ctx->keystates &= ~g_keys[idx].bitmask;
			break ;
		}
		idx++;
	}
}

void		wolf3d_events(t_ctx *ctx)
{
	SDL_Event	event;
	int			ret;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			ctx->state = QUIT;
			break ;
		}
		ret = ctx->states[ctx->state].evt_fn == NULL
			|| !ctx->states[ctx->state].evt_fn(ctx, event);
		if (ret && (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP))
			wolf3d_keys(ctx, &event);
	}
}
