/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 10:44:08 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/10 22:36:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "options.h"
#include "lib.h"
#include "winsize.h"
#include "fractol.h"

static void	init_thread_values(t_data *data)
{
	int			idx;
	int			cols_per_thread;
	t_thread	*thread;

	idx = 0;
	cols_per_thread = data->winsize.width / FRACT_MAX_THREADS;
	while (idx < FRACT_MAX_THREADS)
	{
		thread = &data->threads[idx];
		thread->data = data;
		thread->x = cols_per_thread * idx;
		thread->y = 0;
		if (idx + 1 == FRACT_MAX_THREADS)
			thread->width = data->winsize.width;
		else
			thread->width = thread->x + cols_per_thread;
		thread->height = data->winsize.height;
		idx++;
	}
}

static int	init_fractol(t_data *data, int argc, char **argv)
{
	data->opts = parse_opts(argc, argv, "w:h:");
	if (data->opts == NULL)
		return (0);
	data->winsize.width = WIN_WIDTH;
	data->winsize.height = WIN_HEIGHT;
	data->max_iters = 50;
	data->motion.record = 1;
	data->fract_fn = julia;
	data->cam.x_min = -2.0;
	data->cam.y_min = -2.0;
	data->cam.x_max = 2.0;
	data->cam.y_max = 2.0;
	if (!init_mlx(&(data->lib), &(data->winsize)))
		return (0);
	init_thread_values(data);
	return (1);
}

int			main(int argc, char **argv)
{
	t_data		data;
	int			ret;

	ft_memset(&data, 0, sizeof(t_data));
	ret = init_fractol(&data, argc, argv);
	if (!ret)
		ft_dprintf(2, "fract'ol: Unexpected error\n");
	else
	{
		draw_fractal(&data);
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
