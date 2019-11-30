/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:08:08 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/30 13:23:16 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <stdlib.h>
#include "libft.h"
#include "texture_inf.h"
#include "error.h"

static int	convert_pixels(SDL_Surface *surface, t_texture_inf *text_inf)
{
	return (SDL_ConvertPixels(surface->w, surface->h
			, surface->format->format, surface->pixels
			, surface->pitch, SDL_PIXELFORMAT_ARGB8888
			, text_inf->pixels, surface->w * sizeof(uint32_t)));
}

t_error		load_texture(const char *file, t_texture_inf *text_inf)
{
	t_error		err;
	SDL_Surface	*surface;

	surface = SDL_LoadBMP(file);
	if (surface == NULL)
		err = ERR_LIBSDL2;
	else
	{
		text_inf->pixels = (uint32_t *)malloc(surface->w * surface->h
			* sizeof(uint32_t));
		if (text_inf->pixels == NULL)
			err = ERR_UNEXPECTED;
		else if (convert_pixels(surface, text_inf) < 0)
			err = ERR_LIBSDL2;
		else
		{
			err = ERR_NOERROR;
			text_inf->width = surface->w;
			text_inf->height = surface->h;
		}
		SDL_FreeSurface(surface);
	}
	if (err != ERR_NOERROR)
		ft_memdel((void **)&text_inf->pixels);
	return (err);
}
