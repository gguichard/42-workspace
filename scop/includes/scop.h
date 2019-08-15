/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 10:34:27 by gguichar          #+#    #+#             */
/*   Updated: 2019/08/15 13:56:51 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <OpenGL/gl.h>
# include "winsize.h"
# include "lib_mlx.h"
# include "error.h"

typedef struct		s_scop
{
	t_mlx			lib;
	t_winsize		winsize;
}					t_scop;

t_error				load_shader(const char *file_path, GLenum shader_type);

/*
** HOOKS.
*/
int					loop_hook(t_scop *scop);
int					expose_hook(t_scop *scop);
int					exit_window(t_scop *scop);

#endif
