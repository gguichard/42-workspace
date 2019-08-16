/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 10:34:27 by gguichar          #+#    #+#             */
/*   Updated: 2019/08/16 11:39:00 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <OpenGL/gl3.h>
# include "winsize.h"
# include "lib_mlx.h"
# include "gl_program.h"

typedef struct		s_scop
{
	t_mlx			lib;
	t_winsize		winsize;
	t_gl_program	gl_program;
}					t_scop;

/*
** HOOKS.
*/
int					loop_hook(t_scop *scop);
int					expose_hook(t_scop *scop);
int					exit_window(t_scop *scop);

#endif
