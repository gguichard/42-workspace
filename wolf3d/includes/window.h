/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:01:17 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/10 12:44:42 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include <SDL.h>
# include "error.h"

typedef struct	s_win_size
{
	int			width;
	int			height;
}				t_win_size;

typedef struct	s_win_data
{
	const char		*title;
	t_win_size		size;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	uint32_t		*pixels;
}				t_win_data;

t_error			window_create(t_win_data *win_data);
void			window_destroy(t_win_data *win_data);

#endif
