/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:54:29 by gguichar          #+#    #+#             */
/*   Updated: 2019/08/16 13:58:40 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERROR_BUFF_SIZE 4096

typedef enum	e_error
{
	ERR_NOERROR,
	ERR_UNEXPECTED,
	ERR_ERRNO,
	ERR_MLXINIT,
	ERR_OPENGL,
	ERR_OVERFLOW,
	ERR_SHADERCOMPILE,
	ERR_BADOBJFILE
}				t_error;

char			*error_buffer(const char *new_error);
const char		*error_to_str(t_error error);

#endif