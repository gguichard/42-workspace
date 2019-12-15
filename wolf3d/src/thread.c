/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:26:55 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/05 14:47:07 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include "wolf3d.h"
#include "thread_inf.h"

void	player_view_raycast(t_ctx *ctx)
{
	t_thread_inf	threads[THREADS_COUNT];
	size_t			idx;

	idx = 0;
	while (idx < THREADS_COUNT)
	{
		threads[idx].data = ctx;
		threads[idx].x_start = idx;
		threads[idx].thread = SDL_CreateThread((void *)player_view_thread
				, "Wolf3D", &threads[idx]);
		idx++;
	}
	idx = 0;
	while (idx < THREADS_COUNT)
	{
		if (threads[idx].thread != NULL)
			SDL_WaitThread(threads[idx].thread, NULL);
		idx++;
	}
}
