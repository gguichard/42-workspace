/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 11:53:46 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/10 19:52:42 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "libft.h"
#include "fractol.h"
#include "keys.h"
#include <stdlib.h>

int	expose_hook(t_data *data)
{
	char	*str;

	mlx_put_image_to_window(data->lib.mlx_ptr
			, data->lib.win_ptr
			, data->lib.img_ptr
			, 0, 0);
	str = NULL;
	ft_asprintf(&str, "Iterations : %d", data->max_iters);
	if (str != NULL)
	{
		mlx_string_put(data->lib.mlx_ptr
				, data->lib.win_ptr
				, 50, data->winsize.height - 50
				, 0xFFFFFF, str);
		free(str);
	}
	return (0);
}

int	loop_hook(t_data *data)
{
	if (data->keys.iters != 0)
	{
		data->max_iters += data->keys.iters;
		if (data->max_iters < 0)
			data->max_iters = 0;
		else if (data->max_iters > 300)
			data->max_iters = 300;
		draw_fractal(data);
		expose_hook(data);
	}
	return (0);
}

int	keypress_hook(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		exit_lib(data);
	if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		data->keys.iters = (keycode == KEY_PLUS) ? 5 : -5;
	return (0);
}

int	keyrelease_hook(int keycode, t_data *data)
{
	if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		data->keys.iters = 0;
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	double	x_off;
	double	y_off;
	double	mul;

	(void)x;
	(void)y;
	if (button == KEY_MOUSELEFT)
		data->motion.record = !data->motion.record;
	else if (button == KEY_SCROLLUP || button == KEY_SCROLLDOWN)
	{
		x_off = x / (double)data->winsize.width;
		y_off = y / (double)data->winsize.height;
		mul = (button == KEY_SCROLLUP) ? -.2 : .2;
		data->cam.x_min += x_off * mul;
		data->cam.y_min += y_off * mul;
		data->cam.x_max -= (1 - x_off) * mul;
		data->cam.y_max -= (1 - y_off) * mul;
		draw_fractal(data);
		expose_hook(data);
	}
	return (0);
}

int	motion_hook(int x, int y, t_data *data)
{
	if (data->motion.record)
	{
		data->motion.x = (x - data->winsize.width / 2.0) * 4.0
			/ data->winsize.width;
		data->motion.y = (y - data->winsize.height / 2.0) * 4.0
			/ data->winsize.height;
		draw_fractal(data);
		expose_hook(data);
	}
	return (0);
}

int	exit_lib(t_data *data)
{
	destroy_mlx(&(data->lib));
	exit(0);
	return (0);
}
