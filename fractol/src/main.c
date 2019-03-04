/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 10:44:08 by gguichar          #+#    #+#             */
/*   Updated: 2019/03/04 15:09:42 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "options.h"
#include "lib.h"
#include "winsize.h"
#include "fractol.h"

static void	show_help(t_opts *opts, char **argv)
{
	if (opts->error != 0)
		ft_dprintf(2, "%s: illegal option -- %c\n", argv[0], opts->error);
	ft_printf("USAGE: fractol [options] <fractal>\n");
	ft_printf("<fractal> can be any type of %s\n\n"
			, "Julia, Mandelbrot, Tricorn, BurningShip");
	ft_printf("OPTIONS:\n");
	ft_printf("  -g\tEnable GPU rendering\n");
	ft_printf("  -n\tNetwork computing\n");
	ft_printf("  -h\tShow this help\n");
}

static int	setup_opts(t_data *data, int argc, char **argv)
{
	if (data->opts->error != 0)
		return (0);
	data->winsize.width = WIN_WIDTH;
	data->winsize.height = WIN_HEIGHT;
	if (!setup_fractal_type(data, argc, argv))
	{
		ft_dprintf(2, "%s: Bad fractal name\n\n", argv[0]);
		return (0);
	}
	if (has_opt(data->opts, 'n') && setup_network(data))
		data->draw_fn = draw_network;
	else if (has_opt(data->opts, 'g') && setup_opencl(data))
		data->draw_fn = draw_gpu;
	if (data->draw_fn == NULL)
	{
		if (has_opt(data->opts, 'n') || has_opt(data->opts, 'g'))
			ft_printf("Falling back to multi-threaded version\n");
		init_thread_values(data);
	}
	return (1);
}

static int	init_fractol(t_data *data, int argc, char **argv)
{
	if ((data->opts = parse_opts(argc, argv, "gn")) == NULL)
	{
		ft_dprintf(2, "%s: Unexpected error\n", argv[0]);
		return (0);
	}
	else if (!setup_opts(data, argc, argv))
	{
		show_help(data->opts, argv);
		return (0);
	}
	data->sampling = 1;
	data->color_mul = 1;
	data->keys.show_hud = 1;
	data->max_iters = 100;
	data->cam.scale = 1.0;
	data->cam.x_min = -2.0;
	data->cam.y_min = -2.0;
	data->cam.x_max = 2.0;
	data->cam.y_max = 2.0;
	if (!init_mlx(&(data->lib), &(data->winsize)) || !init_previews(data))
	{
		ft_dprintf(2, "%s: MLX error\n", argv[0]);
		return (0);
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_data	data;
	int		ret;

	ft_memset(&data, 0, sizeof(t_data));
	ret = init_fractol(&data, argc, argv);
	if (ret)
	{
		data.draw_fn(&data);
		mlx_expose_hook(data.lib.win_ptr, expose_hook, &data);
		mlx_loop_hook(data.lib.mlx_ptr, loop_hook, &data);
		mlx_mouse_hook(data.lib.win_ptr, mouse_hook, &data);
		mlx_hook(data.lib.win_ptr, 2, (1L << 0), keypress_hook, &data);
		mlx_hook(data.lib.win_ptr, 3, (1L << 1), keyrelease_hook, &data);
		mlx_hook(data.lib.win_ptr, 6, 0, motion_hook, &data);
		mlx_hook(data.lib.win_ptr, 17, (1L << 17), exit_lib, &data);
		mlx_loop(data.lib.mlx_ptr);
	}
	return (!ret);
}
