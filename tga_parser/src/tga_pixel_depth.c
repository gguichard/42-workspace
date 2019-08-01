/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_pixel_depth.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 18:40:56 by gguichar          #+#    #+#             */
/*   Updated: 2019/08/01 18:54:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "tga_parser.h"

t_tga_error	parse_16bits_tga(uint8_t *data, t_tga_image *image)
{
	size_t	idx;
	uint8_t	rgba[4];

	idx = 0;
	while (idx < image->width * image->height)
	{
		rgba[0] = data[idx * 2] & 0x1F;
		rgba[1] = ((data[idx * 2 + 1] & 0x3) << 3) | (data[idx * 2] >> 5);
		rgba[2] = (data[idx * 2 + 1] >> 2) & 0x1F;
		rgba[3] = (data[idx * 2 + 1] >> 7) * 255;
		rgba[0] = (rgba[0] << 3) | (rgba[0] >> 2);
		rgba[1] = (rgba[1] << 3) | (rgba[1] >> 2);
		rgba[2] = (rgba[2] << 3) | (rgba[2] >> 2);
		image->pixels[idx] = *((uint32_t *)rgba);
		idx++;
	}
	return (TGAERR_NOERROR);
}

t_tga_error	parse_24bits_tga(uint8_t *data, t_tga_image *image)
{
	size_t	idx;
	uint8_t	rgba[4];

	idx = 0;
	while (idx < image->width * image->height)
	{
		rgba[0] = data[idx * 3];
		rgba[1] = data[idx * 3 + 1];
		rgba[2] = data[idx * 3 + 2];
		rgba[3] = 0;
		image->pixels[idx] = *((uint32_t *)rgba);
		idx++;
	}
	return (TGAERR_NOERROR);
}

t_tga_error	parse_32bits_tga(uint8_t *data, t_tga_image *image)
{
	size_t	idx;
	uint8_t	rgba[4];

	idx = 0;
	while (idx < image->width * image->height)
	{
		rgba[0] = data[idx * 4 + 1];
		rgba[1] = data[idx * 4 + 2];
		rgba[2] = data[idx * 4 + 3];
		rgba[3] = data[idx * 4];
		image->pixels[idx] = *((uint32_t *)rgba);
		idx++;
	}
	return (TGAERR_NOERROR);
}
