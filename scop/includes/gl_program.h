/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_program.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 11:25:36 by gguichar          #+#    #+#             */
/*   Updated: 2019/08/16 12:59:36 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_PROGRAM_H
# define GL_PROGRAM_H

# include <OpenGL/gl3.h>
# include "error.h"

typedef struct	s_gl_program
{
	GLuint		program;
	GLuint		vertex_array;
	GLuint		vertex_buffer;
	GLuint		vertex_shader;
	GLuint		fragment_shader;
}				t_gl_program;

t_error			gl_create_program(t_gl_program *gl_program
	, const char *vertex_shader, const char *fragment_shader);
t_error			gl_load_shader(GLuint *shader, const char *file_path
	, GLenum shader_type);

#endif
