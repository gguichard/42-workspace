/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 16:48:39 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/21 20:20:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "libft.h"
#include "tga_parser.h"

static t_tga_error	parse_truecolor_tga(t_tga_header *header
	, t_tga_image *image)
{
	t_tga_error	err;
	int			pixel_depth;
	int			bytes_per_pixel;
	uint8_t		*image_data;

	err = TGAERR_NOERROR;
	pixel_depth = header->image_spec.pixel_depth;
	bytes_per_pixel = pixel_depth / 8 + (pixel_depth % 8 != 0);
	image_data = (uint8_t *)((uintptr_t)(header + 1) + header->id_length);
	if (((uintptr_t)image_data + image->width * image->height * bytes_per_pixel)
		> ((uintptr_t)header + image->file_stat.st_size))
		err = TGAERR_IMAGEDATACORRUPTED;
	else if (pixel_depth == 16)
		err = parse_16bits_tga(image_data, image);
	else if (pixel_depth == 24)
		err = parse_24bits_tga(image_data, image);
	else if (pixel_depth == 32)
		err = parse_32bits_tga(image_data, image);
	else
		err = TGAERR_UNSUPPORTEDPIXELDEPTH;
	return (err);
}

static t_tga_error	parse_tga(t_tga_header *header, t_tga_image *image)
{
	t_tga_error	err;

	if ((size_t)image->file_stat.st_size < sizeof(t_tga_header))
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
	void		*ptr;

	err = TGAERR_NOERROR;
	fd = open(path, O_RDONLY);
	ptr = MAP_FAILED;
	if (fd == -1)
		err = TGAERR_ERRNO;
	else if (fstat(fd, &image->file_stat) == -1)
		err = TGAERR_ERRNO;
	else
	{
		ptr = mmap(NULL, image->file_stat.st_size, PROT_READ, MAP_PRIVATE, fd
				, 0);
		if (ptr == MAP_FAILED)
			err = TGAERR_ERRNO;
		else
			err = parse_tga((t_tga_header *)ptr, image);
	}
	if (ptr != MAP_FAILED)
		munmap(ptr, image->file_stat.st_size);
	if (fd != -1)
		close(fd);
	return (err);
}

void				release_tga_file(t_tga_image *image)
{
	free(image->pixels);
	ft_memset(image, 0, sizeof(t_tga_image));
}
