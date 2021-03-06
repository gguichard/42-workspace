/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 16:49:43 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/21 18:25:02 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_PARSER_H
# define TGA_PARSER_H

# include <stdint.h>
# include <sys/stat.h>

typedef enum	e_tga_error
{
	TGAERR_NOERROR,
	TGAERR_ERRNO,
	TGAERR_CORRUPTED,
	TGAERR_MEMORY,
	TGAERR_UNSUPPORTEDCOLORMAP,
	TGAERR_UNSUPPORTEDIMAGETYPE,
	TGAERR_UNSUPPORTEDPIXELDEPTH,
	TGAERR_IMAGEDATACORRUPTED
}				t_tga_error;

# pragma pack(push, 1)

typedef struct	s_tga_color_map
{
	uint16_t	first_entry_index;
	uint16_t	color_map_length;
	uint8_t		color_map_entry_size;
}				t_tga_color_map;

typedef struct	s_tga_image_spec
{
	uint16_t	x_origin;
	uint16_t	y_origin;
	uint16_t	image_width;
	uint16_t	image_height;
	uint8_t		pixel_depth;
	uint8_t		image_descriptor;
}				t_tga_image_spec;

typedef struct	s_tga_header
{
	uint8_t				id_length;
	uint8_t				color_map_type;
	uint8_t				image_type;
	t_tga_color_map		color_map;
	t_tga_image_spec	image_spec;
}				t_tga_header;

# pragma pack(pop)

typedef struct	s_tga_image
{
	uint16_t	width;
	uint16_t	height;
	uint32_t	*pixels;
	struct stat	file_stat;
}				t_tga_image;

t_tga_error		parse_16bits_tga(uint8_t *data, t_tga_image *image);
t_tga_error		parse_24bits_tga(uint8_t *data, t_tga_image *image);
t_tga_error		parse_32bits_tga(uint8_t *data, t_tga_image *image);

t_tga_error		load_tga_file(const char *path, t_tga_image *image);
void			release_tga_file(t_tga_image *image);

#endif
