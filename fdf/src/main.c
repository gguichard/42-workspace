/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:34:22 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/09 18:49:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "fdf.h"
#include "matrix44.h"

int			clean_fdf(t_fdf *fdf)
{
	if (fdf->lib.win_ptr != NULL)
		mlx_destroy_window(fdf->lib.mlx_ptr, fdf->lib.win_ptr);
	if (fdf->lib.img_ptr != NULL)
		mlx_destroy_image(fdf->lib.mlx_ptr, fdf->lib.img_ptr);
	ft_lstfree(&(fdf->palette));
	ft_vecfree(&(fdf->pos));
	ft_memdel((void *)&(fdf->z_buffer));
	return (0);
}

static int	init_mlx(t_fdf *fdf)
{
	if (!(fdf->lib.mlx_ptr = mlx_init()))
		return (0);
	fdf->lib.win_ptr = mlx_new_window(fdf->lib.mlx_ptr
			, fdf->winsize.width, fdf->winsize.height
			, "FDF");
	if (!(fdf->lib.win_ptr))
		return (0);
	fdf->lib.img_ptr = mlx_new_image(fdf->lib.mlx_ptr
			, fdf->winsize.width, fdf->winsize.height);
	if (!(fdf->lib.img_ptr))
		return (0);
	fdf->lib.img_data = (unsigned int *)mlx_get_data_addr(fdf->lib.img_ptr
			, &(fdf->lib.bits_per_pixel)
			, &(fdf->lib.size_line)
			, &(fdf->lib.endian));
	if (!(fdf->lib.img_data))
		return (0);
	return (1);
}

static int	init_fdf(t_fdf *fdf, int argc, char **argv)
{
	parse_opts(&fdf->opts, argv, "w:h:p:o");
	fdf->argc = argc - fdf->opts.index;
	fdf->argv = argv + fdf->opts.index;
	if (!check_options(fdf))
		return (0);
	fdf->z_buffer = (int *)malloc(fdf->winsize.width * fdf->winsize.height
			* sizeof(int));
	if (!fdf->z_buffer)
		return (0);
	mat44_identity(fdf->matrix);
	mat44_identity(fdf->matrix_translate);
	return (1);
}

static int	init_obj_file(t_fdf *fdf)
{
	t_error	err;
	size_t	idx;
	t_pos	*pos;

	err = parse_wf_obj_file((fdf->argv)[0], &fdf->objfile, 5);
	if (err != ERR_NOERROR)
		return (0);
	idx = 0;
	while (idx < fdf->objfile.vertices.size)
	{
		pos = ft_memalloc(sizeof(t_pos));
		if (pos == NULL)
			break ;
		pos->x = ((t_vec3d *)fdf->objfile.vertices.data[idx])->x;
		pos->y = ((t_vec3d *)fdf->objfile.vertices.data[idx])->y;
		pos->z = ((t_vec3d *)fdf->objfile.vertices.data[idx])->z;
		pos->color = 0xFFFFFF;
		if (!ft_vecpush(&fdf->pos, pos))
			break ;
		idx++;
	}
	free_wf_obj(&fdf->objfile);
	return (1);
}

static int	init(t_fdf *fdf, int argc, char **argv)
{
	if (!init_fdf(fdf, argc, argv))
		return (0);
	if (fdf->opts.error != 0 || fdf->argc <= 0)
		return (print_usage(fdf));
	if (has_opt(&fdf->opts, 'o'))
	{
		if (!init_obj_file(fdf))
		{
			ft_dprintf(STDERR_FILENO, "fdf: unable to parse obj file\n");
			return (0);
		}
		fdf->use_obj_render = 1;
	}
	else
	{
		fdf->pos = read_file((fdf->argv)[0], fdf);
		if (fdf->pos.size == 0)
		{
			ft_dprintf(STDERR_FILENO, "fdf: unable to parse map file\n");
			return (0);
		}
	}
	ft_lstfree(&(fdf->palette));
	if (!init_mlx(fdf))
	{
		ft_dprintf(STDERR_FILENO, "fdf: unable to init minilibx\n");
		return (0);
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_fdf	fdf;

	ft_memset(&fdf, 0, sizeof(t_fdf));
	if (!init(&fdf, argc, argv))
	{
		clean_fdf(&fdf);
		return (1);
	}
	fill_window_image(&fdf);
	mlx_loop_hook(fdf.lib.mlx_ptr, loop_hook, &fdf);
	mlx_expose_hook(fdf.lib.win_ptr, expose_hook, &fdf);
	mlx_hook(fdf.lib.win_ptr, 17, (1L << 17), exit_fdf, &fdf);
	mlx_hook(fdf.lib.win_ptr, 2, (1L << 0), keypress_hook, &fdf);
	mlx_hook(fdf.lib.win_ptr, 3, (1L << 1), keyrelease_hook, &fdf);
	mlx_hook(fdf.lib.win_ptr, 4, (1L << 2), button_hook, &fdf);
	mlx_hook(fdf.lib.win_ptr, 5, (1L << 3), button_hook, &fdf);
	mlx_hook(fdf.lib.win_ptr, 6, (1L << 13), motion_hook, &fdf);
	mlx_loop(fdf.lib.mlx_ptr);
	return (0);
}
