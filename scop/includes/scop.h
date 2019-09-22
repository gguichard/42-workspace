/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 10:34:27 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/22 14:50:23 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <OpenGL/gl3.h>
# include "window.h"

typedef struct		s_scop
{
	t_win_data		win_data;
}					t_scop;

/*
** HOOKS.
*/
void				run_window_loop(t_win_data *win_data);

#endif
