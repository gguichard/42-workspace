/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:34:22 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/31 07:03:09 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
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

static int	init_fdf(t_fdf *fdf, int argc, char **argv)
{
	fdf->opt = parse_opts(argc, argv, "w:h:p:");
	fdf->argc = argc - fdf->opt->index;
	fdf->argv = argv + fdf->opt->index;
	fdf->palette = NULL;
	if (!check_options(fdf))
		return (0);
	ft_memset(&(fdf->cam), 0, sizeof(t_cam));
	fdf->scale = 30;
	fdf->depth = 10;
	fdf->angle = 45;
	fdf->angle_sin = sin(fdf->angle * M_PI / 180.0);
	fdf->angle_cos = cos(fdf->angle * M_PI / 180.0);
	fdf->proj = ISO;
	fdf->f_proj = &iso;
	fdf->offset_x = 0;
	fdf->offset_y = 0;
	ft_memset(&(fdf->move), 0, sizeof(t_move));
	return (1);
}

static int	init(t_fdf *fdf, int argc, char **argv)
{
	if (!init_fdf(fdf, argc, argv))
		return (0);
	if (fdf->opt->error != 0 || fdf->argc <= 0)
	{
		if (fdf->opt->error)
			ft_dprintf(2, "fdf: illegal option -- %c\n", fdf->opt->error);
		ft_printf("USAGE: ./fdf [options] <map_file>\n\n");
		ft_printf("OPTIONS:\n");
		ft_printf("  -w <size>\tSpecify width for window size\n");
		ft_printf("  -h <size>\tSpecify height for window size\n");
		ft_printf("  -p <file>\tUse file as color palette\n");
		return (0);
	}
	if (!read_file((fdf->argv)[0], fdf))
	{
		ft_dprintf(2, "fdf: unable to parse map file\n");
		return (0);
	}
	if (!init_mlx(fdf))
	{
		ft_dprintf(2, "fdf: unable to init minilibx\n");
		return (0);
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_fdf	fdf;

	if (!init(&fdf, argc, argv))
		return (1);
	fill_window_image(&fdf);
	mlx_loop_hook(fdf.lib.mlx_ptr, &loop_hook, &fdf);
	mlx_expose_hook(fdf.lib.win_ptr, &expose_hook, &fdf);
	mlx_hook(fdf.lib.win_ptr, 17, (1L << 17), &exit_fdf, &fdf);
	mlx_hook(fdf.lib.win_ptr, 2, (1L << 0), &keypress_hook, &fdf);
	mlx_hook(fdf.lib.win_ptr, 3, (1L << 1), &keyrelease_hook, &fdf);
	mlx_loop(fdf.lib.mlx_ptr);
	return (0);
}
