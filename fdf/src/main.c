/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:34:22 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/10 17:58:49 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "fdf.h"
#include "error.h"
#include "matrix44.h"

int				clean_fdf(t_fdf *fdf)
{
	clean_mlx(&fdf->lib);
	ft_lstfree(&(fdf->palette));
	ft_vecfree(&(fdf->pos));
	ft_memdel((void *)&(fdf->z_buffer));
	return (0);
}

static t_error	init_fdf(t_fdf *fdf, int argc, char **argv)
{
	parse_opts(&fdf->opts, argv, "w:h:p:o");
	fdf->argc = argc - fdf->opts.index;
	fdf->argv = argv + fdf->opts.index;
	if (fdf->opts.error != 0 || fdf->argc <= 0)
		return (ERR_SHOWUSAGE);
	else if (!check_options(fdf))
		return (ERR_BADOPTIONS);
	fdf->z_buffer = (int *)malloc(fdf->winsize.width * fdf->winsize.height
			* sizeof(int));
	if (!fdf->z_buffer)
		return (ERR_UNEXPECTED);
	mat44_identity(fdf->matrix);
	mat44_identity(fdf->matrix_translate);
	return (ERR_NOERROR);
}

static t_error	parse_map_file(t_fdf *fdf)
{
	t_error	err;

	err = ERR_NOERROR;
	if (!has_opt(&fdf->opts, 'o'))
		err = read_file(fdf);
	else
	{
		err = read_obj_file(fdf);
		fdf->use_obj_render = 1;
	}
	ft_lstfree(&(fdf->palette));
	return (err);
}

static int		clean_and_print_error(t_fdf *fdf, t_error err)
{
	clean_fdf(fdf);
	if (err == ERR_SHOWUSAGE)
		print_usage(fdf);
	else if (err != ERR_BADOPTIONS)
		ft_dprintf(STDERR_FILENO, "fdf: error: %s\n", error_to_str(err));
	return (1);
}

int				main(int argc, char **argv)
{
	t_fdf	fdf;
	t_error	err;

	ft_memset(&fdf, 0, sizeof(t_fdf));
	err = init_fdf(&fdf, argc, argv);
	if (err == ERR_NOERROR)
		err = parse_map_file(&fdf);
	if (err == ERR_NOERROR && !init_mlx(&fdf.lib, fdf.winsize))
		err = ERR_MLXINIT;
	if (err != ERR_NOERROR)
		return (clean_and_print_error(&fdf, err));
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
