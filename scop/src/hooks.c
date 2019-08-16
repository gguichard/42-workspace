/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 04:05:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/08/16 11:39:28 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <OpenGL/gl3.h>
#include "mlx_opengl.h"
#include "scop.h"

int	expose_hook(t_scop *scop)
{
	(void)scop;
	return (0);
}

int	loop_hook(t_scop *scop)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(scop->gl_program.program);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	mlx_opengl_swap_buffers(scop->lib.win_ptr);
	return (0);
}

int	exit_window(t_scop *scop)
{
	(void)scop;
	exit(0);
	return (0);
}
