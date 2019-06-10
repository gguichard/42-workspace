/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:54:29 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/10 20:10:01 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum	e_error
{
	ERR_NOERROR,
	ERR_UNEXPECTED,
	ERR_ERRNO,
	ERR_WRONGMAPFILE,
	ERR_BADOBJFILE,
	ERR_SHOWUSAGE,
	ERR_MLXINIT,
	ERR_WRONGPALETTEFILE
}				t_error;

const char		*error_to_str(t_error error);

#endif
