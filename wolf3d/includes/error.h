/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 19:54:57 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/27 23:04:00 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum	e_error
{
	ERR_NOERROR = 0,
	ERR_USAGE,
	ERR_UNEXPECTED,
	ERR_LIBSDL2,
	ERR_ERRNO,
	ERR_MAPTILE,
	ERR_MAPNOPLAYER
}				t_error;

const char		*error_to_str(t_error err);

#endif
