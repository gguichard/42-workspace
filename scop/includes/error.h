/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:54:29 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/22 14:48:02 by gguichar         ###   ########.fr       */
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
	ERR_SDLINIT,
	ERR_CUSTOM,
	ERR_BADOBJFILE
}				t_error;

char			*error_buffer(const char *new_error);
const char		*error_to_str(t_error error);

#endif
