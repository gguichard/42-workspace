/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 04:05:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/22 14:50:46 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "scop.h"
#include "window.h"

static int	poll_events(void)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT
			|| (event.type == SDL_KEYDOWN
				&& event.key.keysym.sym == SDLK_ESCAPE)
			|| (event.type == SDL_WINDOWEVENT
				&& event.window.event == SDL_WINDOWEVENT_CLOSE))
			return (0);
	}
	return (1);
}

void		run_window_loop(t_win_data *win_data)
{
	while (1)
	{
		if (!poll_events())
			break ;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SDL_GL_SwapWindow(win_data->window);
	}
}
