/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:17:51 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/10 17:41:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "error.h"

const char	*error_to_str(t_error error)
{
	if (error == ERR_UNEXPECTED)
		return ("Unexpected error");
	else if (error == ERR_ERRNO)
		return (strerror(errno));
	else if (error == ERR_BADOBJFILE)
		return ("Bad wavefront obj file\n");
	else
		return ("Unknown error");
}
