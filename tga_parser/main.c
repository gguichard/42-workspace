/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 17:26:07 by gguichar          #+#    #+#             */
/*   Updated: 2019/08/01 18:39:47 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "mlx.h"
#include "tga_parser.h"

static void	open_mlx_window(t_tga_image image)
{
	void	*mlx_ptr;
	void	*win_ptr;
	size_t	x;
	size_t	y;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, image.width, image.height, "TGA VIEWER");
	x = 0;
	while (x < image.width)
	{
		y = 0;
		while (y < image.height)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x, y
				, image.pixels[y * image.width + x]);
			y++;
		}
		x++;
	}
	mlx_loop(mlx_ptr);
}

int			main(int argc, char **argv)
{
	t_tga_error	err;
	t_tga_image	tga_image;

	if (argc != 2)
	{
		fprintf(stderr, "missing file name\n");
		return (EXIT_FAILURE);
	}
	err = load_tga_file(argv[1], &tga_image);
	if (err != TGAERR_NOERROR)
		fprintf(stderr, "unable to load %s (error=%d)\n", argv[1], err);
	else
	{
		fprintf(stdout, "%s\nwidth: %hu | height: %hu\n", argv[1]
			, tga_image.width, tga_image.height);
		open_mlx_window(tga_image);
	}
	return (EXIT_SUCCESS);
}
