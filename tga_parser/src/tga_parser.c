/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 16:48:39 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/31 19:47:24 by gguichar         ###   ########.fr       */
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

static void			parse_truecolor_tga(uint32_t *data, t_tga_image *image)
{
	(void)data;
	(void)image;
}

static t_tga_error	parse_tga(t_tga_header *header, t_tga_image *image
	, struct stat buf)
{
	t_tga_error	err;

	if ((size_t)buf.st_size < sizeof(t_tga_header))
		err = TGAERR_CORRUPTED;
	else
	{
		err = TGAERR_NOERROR;
		memset(image, 0, sizeof(t_tga_image));
		image->width = header->image_spec.image_width;
		image->height = header->image_spec.image_height;
		image->pixels = (uint32_t *)malloc(sizeof(uint32_t) * image->width
				* image->height);
		if (image->pixels == NULL)
			err = TGAERR_MEMORY;
		else if (header->image_type == 2)
			parse_truecolor_tga((uint32_t *)
				((uintptr_t)header + sizeof(t_tga_header) + header->id_length)
				, image);
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
