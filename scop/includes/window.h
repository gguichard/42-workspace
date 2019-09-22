/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 12:20:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/22 14:39:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include <SDL.h>
# include "error.h"
# include "winsize.h"

# define WIN_TITLE "Scop"
# define WIN_WIDTH 1640
# define WIN_HEIGHT 1280

typedef struct	s_win_data
{
	const char		*title;
	t_winsize		size;
	SDL_Window		*window;
	SDL_GLContext	context;
}				t_win_data;

t_error			create_context_window(t_win_data *win_data);
void			destroy_window(t_win_data *win_data);

#endif
