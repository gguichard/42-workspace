/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_program.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 11:27:37 by gguichar          #+#    #+#             */
/*   Updated: 2019/08/16 14:02:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenGL/gl3.h>
#include "libft.h"
#include "gl_program.h"

t_error	gl_create_program(t_gl_program *gl_program, const char *vertex_shader
	, const char *fragment_shader)
{
	t_error			err;
	static float	vertices[] = {
		0.5, -0.5, 0.0,
		0.0, 0.5, 0.0,
		-0.5, -0.5, 0.0
	};

	err = ERR_NOERROR;
	ft_memset(gl_program, 0, sizeof(t_gl_program));
	glGenBuffers(1, &gl_program->vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, gl_program->vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenVertexArrays(1, &gl_program->vertex_array);
	glBindVertexArray(gl_program->vertex_array);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, gl_program->vertex_buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	gl_program->program = glCreateProgram();
	if (gl_program->program == 0)
		err = ERR_OPENGL;
	else
	{
		err = gl_load_shader(&gl_program->vertex_shader, vertex_shader
			, GL_VERTEX_SHADER);
		if (err == ERR_NOERROR)
			err = gl_load_shader(&gl_program->fragment_shader, fragment_shader
				, GL_FRAGMENT_SHADER);
		if (err == ERR_NOERROR)
		{
			glAttachShader(gl_program->program, gl_program->vertex_shader);
			glAttachShader(gl_program->program, gl_program->fragment_shader);
		}
		glLinkProgram(gl_program->program);
	}
	return (err);
}
