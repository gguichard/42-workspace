/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:22:59 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/15 15:02:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <SDL.h>
#include "wolf3d.h"
#include "keystates.h"

static uint64_t	wolf3d_key(int keycode)
{
	static t_key	keys[] = {
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
	size_t			idx;

	idx = 0;
	while (idx < (sizeof(keys) / sizeof(keys[0])))
	{
		if (keys[idx].keycode == keycode)
			return (keys[idx].bitmask);
		idx++;
	}
	return (0);
}

static void		wolf3d_handle_keys(t_ctx *ctx, SDL_Event *event)
{
	uint64_t	bitmask;

	bitmask = wolf3d_key(event->key.keysym.sym);
	if (event->type == SDL_KEYDOWN)
		ctx->keystates |= bitmask;
	else
		ctx->keystates &= ~bitmask;
}

void			wolf3d_events(t_ctx *ctx)
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
			wolf3d_handle_keys(ctx, &event);
	}
}
