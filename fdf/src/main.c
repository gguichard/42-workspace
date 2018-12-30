/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:34:22 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/30 05:37:18 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"

int			clean_mlx(t_fdf *fdf)
{
	if (fdf->lib.win_ptr != NULL)
		mlx_destroy_window(fdf->lib.mlx_ptr, fdf->lib.win_ptr);
	if (fdf->lib.img_ptr != NULL)
		mlx_destroy_image(fdf->lib.mlx_ptr, fdf->lib.img_ptr);
	return (0);
}

static int	init_mlx(t_fdf *fdf)
{
	ft_memset(&(fdf->lib), 0, sizeof(t_mlx));
	if (!(fdf->lib.mlx_ptr = mlx_init()))
		return (0);
	fdf->lib.win_ptr = mlx_new_window(fdf->lib.mlx_ptr
			, fdf->width, fdf->height
			, "FDF");
	if (!(fdf->lib.win_ptr))
		return (0);
	fdf->lib.img_ptr = mlx_new_image(fdf->lib.mlx_ptr, fdf->width, fdf->height);
	if (!(fdf->lib.img_ptr))
		return (clean_mlx(fdf));
	fdf->lib.img_data = (unsigned int *)mlx_get_data_addr(fdf->lib.img_ptr
			, &(fdf->lib.bits_per_pixel)
			, &(fdf->lib.size_line)
			, &(fdf->lib.endian));
	if (!(fdf->lib.img_data))
		return (clean_mlx(fdf));
	return (1);
}

static int	init_fdf(t_fdf *fdf)
{
	fdf->width = WIN_WIDTH;
	fdf->height = WIN_HEIGHT;
	fdf->scale = 20;
	fdf->depth = 1;
	return (init_mlx(fdf));
}

int			main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc < 2)
	{
		ft_dprintf(2, "usage: ./fdf [map_file]\n");
		return (1);
	}
	if (!read_file(argv[1], &fdf))
	{
		ft_dprintf(2, "fdf: unable to parse map file\n");
		return (1);
	}
	if (!init_fdf(&fdf))
	{
		ft_dprintf(2, "fdf: unable to init minilibx\n");
		return (1);
	}
	fill_window_image(&fdf);
	mlx_hook(fdf.lib.win_ptr, 17, (1L << 17), &exit_fdf, &fdf);
	mlx_key_hook(fdf.lib.win_ptr, &key_hook, &fdf);
	mlx_expose_hook(fdf.lib.win_ptr, &expose_hook, &fdf);
	mlx_loop(fdf.lib.mlx_ptr);
	return (0);
}
