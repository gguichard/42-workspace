/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:54:29 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/09 17:55:33 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum	e_error
{
	ERR_NOERROR,
	ERR_UNEXPECTED,
	ERR_ERRNO,
	ERR_BADOBJFILE
}				t_error;

#endif
