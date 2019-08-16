/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_shader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 13:23:43 by gguichar          #+#    #+#             */
/*   Updated: 2019/08/16 11:45:02 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <OpenGL/gl3.h>
#include "libft.h"
#include "scop.h"
#include "error.h"

static t_error	load_shader_content(const char *file_path, char **source
	, GLint *source_len)
{
	t_error		err;
	int			fd;
	struct stat	buf;

	err = ERR_NOERROR;
	fd = open(file_path, O_RDONLY);
	if (fd == -1 || fstat(fd, &buf) == -1)
		err = ERR_ERRNO;
	else
	{
		*source_len = buf.st_size;
		if ((size_t)(*source_len) != (size_t)buf.st_size)
			err = ERR_OVERFLOW;
		else
		{
			*source = (char *)mmap(NULL, *source_len, PROT_READ
				, MAP_PRIVATE, fd, 0);
			if ((void *)(*source) == MAP_FAILED)
				err = ERR_ERRNO;
		}
	}
	if (fd != -1)
		close(fd);
	return (err);
}

t_error			gl_load_shader(GLuint *shader, const char *file_path
	, GLenum shader_type)
{
	t_error	err;
	char	*source;
	GLsizei	source_len;
	GLint	compile_ret;

	err = load_shader_content(file_path, &source, &source_len);
	if (err == ERR_NOERROR)
	{
		*shader = glCreateShader(shader_type);
		glShaderSource(*shader, 1, (const char **)&source, &source_len);
		munmap(source, source_len);
		glCompileShader(*shader);
		glGetShaderiv(*shader, GL_COMPILE_STATUS, &compile_ret);
		if (compile_ret != GL_TRUE)
		{
			err = ERR_SHADERCOMPILE;
			glGetShaderInfoLog(*shader, ERROR_BUFF_SIZE - 1, NULL
				, error_buffer(NULL));
			glDeleteShader(*shader);
		}
	}
	return (err);
}
