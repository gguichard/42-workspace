/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_sdl2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 19:58:01 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/27 20:59:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <stdlib.h>
#include "libft.h"
#include "window.h"
#include "error.h"

t_error	window_create(t_win_data *win_data)
{
	t_error	err;

	err = ERR_NOERROR;
	win_data->window = SDL_CreateWindow(win_data->title
			, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
			, win_data->size.width, win_data->size.height, 0);
	if (win_data->window == NULL)
		err = ERR_LIBSDL2;
	else
	{
		win_data->renderer = SDL_CreateRenderer(win_data->window, -1
			, SDL_RENDERER_PRESENTVSYNC);
		if (win_data->renderer == NULL)
			err = ERR_LIBSDL2;
		else
		{
			win_data->texture = SDL_CreateTexture(win_data->renderer
				, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING
				, win_data->size.width, win_data->size.height);
			if (win_data->texture == NULL)
				err = ERR_LIBSDL2;
		}
	}
	return (err);
}

void	window_destroy(t_win_data *win_data)
{
	if (win_data->window != NULL)
	{
		if (win_data->renderer != NULL)
			SDL_DestroyRenderer(win_data->renderer);
		if (win_data->texture != NULL)
			SDL_DestroyTexture(win_data->texture);
		SDL_DestroyWindow(win_data->window);
		ft_memset(win_data, 0, sizeof(t_win_data));
	}
}
