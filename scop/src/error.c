/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:17:51 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/22 14:48:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <string.h>
#include <errno.h>
#include "libft.h"
#include "error.h"

char		*error_buffer(const char *new_error)
{
	static char	buffer[ERROR_BUFF_SIZE];
	size_t		nlen;

	if (new_error != NULL)
	{
		nlen = ft_strnlen(new_error, ERROR_BUFF_SIZE - 1);
		ft_memcpy(buffer, new_error, nlen);
		buffer[nlen] = '\0';
	}
	return (buffer);
}

const char	*error_to_str(t_error error)
{
	if (error == ERR_UNEXPECTED)
		return ("Unexpected error");
	else if (error == ERR_ERRNO)
		return (strerror(errno));
	else if (error == ERR_SDLINIT)
		return (SDL_GetError());
	else if (error == ERR_CUSTOM)
		return (error_buffer(NULL));
	else if (error == ERR_BADOBJFILE)
		return ("OBJ file malformed");
	else
		return ("Unknown error");
}
