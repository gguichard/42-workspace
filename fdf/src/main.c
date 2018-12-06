/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:34:22 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/06 20:13:47 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"
#include "libft.h"
#include "printf.h"

void	clean_mlx(t_fdf *fdf)
{
	if (fdf->lib.win_ptr != NULL)
		mlx_destroy_window(fdf->lib.mlx_ptr, fdf->lib.win_ptr);
	if (fdf->lib.img_ptr != NULL)
		mlx_destroy_image(fdf->lib.mlx_ptr, fdf->lib.img_ptr);
}

int		init_mlx(t_fdf *fdf)
{
	if (!(fdf->lib.mlx_ptr = mlx_init()))
		return (0);
	fdf->lib.win_ptr = mlx_new_window(fdf->lib.mlx_ptr, fdf->width, fdf->height
			, "FDF");
	if (!(fdf->lib.win_ptr))
		return (0);
	fdf->lib.img_ptr = mlx_new_image(fdf->lib.mlx_ptr, fdf->width, fdf->height);
	if (!(fdf->lib.img_ptr))
	{
		clean_mlx(fdf);
		return (0);
	}
	fdf->lib.img_data = (unsigned int *)mlx_get_data_addr(fdf->lib.img_ptr
			, &(fdf->lib.bits_per_pixel)
			, &(fdf->lib.size_line)
			, &(fdf->lib.endian));
	if (!(fdf->lib.img_data))
	{
		clean_mlx(fdf);
		return (0);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc < 2)
	{
		ft_dprintf(2, "usage: ./fdf [map_file]\n");
		return (1);
	}
	else if (!(read_file(argv[1])))
	{
		ft_dprintf(2, "fdf: unable to parse map file\n");
		return (1);
	}
	fdf.width = WIN_WIDTH;
	fdf.height = WIN_HEIGHT;
	ft_memset(&(fdf.lib), 0, sizeof(t_mlx));
	if (!(init_mlx(&fdf)))
	{
		ft_dprintf(2, "fdf: unable to init minilibx\n");
		return (1);
	}
	mlx_loop(fdf.lib.mlx_ptr);
	return (0);
}
