/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:04:08 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/27 23:04:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <string.h>
#include <errno.h>
#include "error.h"

const char	*error_to_str(t_error err)
{
	if (err == ERR_USAGE)
		return ("usage: ./wolf3d map_file");
	else if (err == ERR_UNEXPECTED)
		return ("unexpected error");
	else if (err == ERR_LIBSDL2)
		return (SDL_GetError());
	else if (err == ERR_ERRNO)
		return (strerror(errno));
	else if (err == ERR_MAPTILE)
		return ("map tile error");
	else if (err == ERR_MAPNOPLAYER)
		return ("no player on map");
	else
		return ("unknown error");
}
