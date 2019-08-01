/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 16:48:39 by gguichar          #+#    #+#             */
/*   Updated: 2019/08/01 19:28:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "tga_parser.h"

static t_tga_error	parse_truecolor_tga(t_tga_header *header
	, t_tga_image *image)
{
	t_tga_error	err;
	uint8_t		*data;
	int			pixel_depth;

	err = TGAERR_NOERROR;
	data = (uint8_t *)((uintptr_t)(header + 1) + header->id_length);
	pixel_depth = header->image_spec.pixel_depth;
	if (pixel_depth == 16)
		err = parse_16bits_tga(data, image);
	else if (pixel_depth == 24)
		err = parse_24bits_tga(data, image);
	else if (pixel_depth == 32)
		err = parse_32bits_tga(data, image);
	else
		err = TGAERR_UNSUPPORTEDPIXELDEPTH;
	return (err);
}

static t_tga_error	parse_tga(t_tga_header *header, t_tga_image *image
	, struct stat buf)
{
	t_tga_error	err;

	if ((size_t)buf.st_size < sizeof(t_tga_header))
		err = TGAERR_CORRUPTED;
	else if (header->color_map_type != 0)
		err = TGAERR_UNSUPPORTEDCOLORMAP;
	else
	{
		err = TGAERR_NOERROR;
		image->width = header->image_spec.image_width;
		image->height = header->image_spec.image_height;
		image->pixels = (uint32_t *)malloc(sizeof(uint32_t) * image->width
				* image->height);
		if (image->pixels == NULL)
			err = TGAERR_MEMORY;
		else if (header->image_type == 2)
			err = parse_truecolor_tga(header, image);
		else
			err = TGAERR_UNSUPPORTEDIMAGETYPE;
		if (err != TGAERR_NOERROR)
			release_tga_file(image);
	}
	return (err);
}

t_tga_error			load_tga_file(const char *path, t_tga_image *image)
{
	t_tga_error	err;
	int			fd;
	struct stat	buf;
	void		*ptr;

	err = TGAERR_NOERROR;
	fd = open(path, O_RDONLY);
	ptr = MAP_FAILED;
	if (fd == -1)
		err = TGAERR_ERRNO;
	else if (fstat(fd, &buf) == -1)
		err = TGAERR_ERRNO;
	else
	{
		ptr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
		if (ptr == MAP_FAILED)
			err = TGAERR_ERRNO;
		else
			err = parse_tga((t_tga_header *)ptr, image, buf);
	}
	if (ptr != MAP_FAILED)
		munmap(ptr, buf.st_size);
	if (fd != -1)
		close(fd);
	return (err);
}

void				release_tga_file(t_tga_image *image)
{
	free(image->pixels);
	image->pixels = NULL;
}
