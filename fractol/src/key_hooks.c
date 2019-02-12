/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 03:29:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/12 09:05:33 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			keypress_hook(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		exit_lib(data);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		data->keys.iters = (keycode == KEY_PLUS) ? 5 : -5;
	else if (keycode == KEY_R)
		reset_draw(data);
	return (0);
}

int			keyrelease_hook(int keycode, t_data *data)
{
	if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		data->keys.iters = 0;
	return (0);
}

static void	handle_mouse_left(t_data *data, int x, int y)
{
	if (x >= data->winsize.width - FRACT_PREVIEWS_WIDTH
			&& y <= FRACT_PREVIEWS * FRACT_PREVIEWS_HEIGHT)
		change_fract_type(data, y / FRACT_PREVIEWS_HEIGHT);
	else
		data->motion.record = !data->motion.record;
}

int			mouse_hook(int button, int x, int y, t_data *data)
{
	double	real_x;
	double	real_y;

	if (button == KEY_MOUSELEFT)
		handle_mouse_left(data, x, y);
	else if (button == KEY_SCROLLUP || button == KEY_SCROLLDOWN)
	{
		data->cam.scale = (button == KEY_SCROLLUP) ? (1 / 1.1) : 1.1;
		real_x = x * (data->cam.x_max - data->cam.x_min)
			/ data->winsize.width + data->cam.x_min;
		real_y = y * (data->cam.y_max - data->cam.y_min)
			/ data->winsize.height + data->cam.y_min;
		data->cam.x_min = real_x - (real_x - data->cam.x_min) * data->cam.scale;
		data->cam.x_max = real_x - (real_x - data->cam.x_max) * data->cam.scale;
		data->cam.y_min = real_y - (real_y - data->cam.y_min) * data->cam.scale;
		data->cam.y_max = real_y - (real_y - data->cam.y_max) * data->cam.scale;
		data->draw_fn(data);
		expose_hook(data);
	}
	return (0);
}

int			motion_hook(int x, int y, t_data *data)
{
	if (data->motion.record)
	{
		data->motion.x = x * (data->cam.x_max - data->cam.x_min)
			/ data->winsize.width + data->cam.x_min;
		data->motion.y = y * (data->cam.y_max - data->cam.y_min)
			/ data->winsize.height + data->cam.y_min;
		if (data->fract_fn == julia)
			data->draw_fn(data);
		draw_preview(data, &data->previews[0], julia);
		expose_hook(data);
	}
	return (0);
}
