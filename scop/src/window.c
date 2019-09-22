/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 12:19:49 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/22 14:46:56 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <stdlib.h>
#include "libft.h"
#include "error.h"
#include "window.h"

t_error	create_context_window(t_win_data *win_data)
{
	t_error	err;

	err = ERR_NOERROR;
	win_data->window = SDL_CreateWindow(win_data->title
			, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
			, win_data->size.width, win_data->size.height, SDL_WINDOW_OPENGL);
	if (win_data->window == NULL)
		err = ERR_SDLINIT;
	else
		win_data->context = SDL_GL_CreateContext(win_data->window);
	return (err);
}

void	destroy_window(t_win_data *win_data)
{
	if (win_data->window != NULL)
	{
		SDL_GL_DeleteContext(win_data->context);
		SDL_DestroyWindow(win_data->window);
		ft_memset(win_data, 0, sizeof(t_win_data));
	}
}
