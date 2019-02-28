/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 03:29:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/28 09:48:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fractol.h"

int			keypress_hook(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		exit_lib(data);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		data->keys.iters = (keycode == KEY_PLUS) ? 5 : -5;
	else if (keycode == KEY_R)
		reset_draw(data);
	else if (keycode == KEY_PAGEUP)
		change_fract_type(data, data->preview_idx - 1);
	else if (keycode == KEY_PAGEDOWN)
		change_fract_type(data, data->preview_idx + 1);
	else if (keycode == KEY_ARROWLEFT || keycode == KEY_ARROWRIGHT)
		data->keys.x_move = (keycode == KEY_ARROWRIGHT) ? 10 : -10;
	else if (keycode == KEY_ARROWUP || keycode == KEY_ARROWDOWN)
		data->keys.y_move = (keycode == KEY_ARROWUP) ? -10 : 10;
	else if (keycode == KEY_SHIFT)
		data->not_epileptic = !data->not_epileptic;
	else if (keycode == KEY_A)
		increase_sampling(data);
	else if (keycode == KEY_TAB)
	{
		data->keys.show_hud = !data->keys.show_hud;
		redraw_all(data);
	}
	return (0);
}

int			keyrelease_hook(int keycode, t_data *data)
{
	if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		data->keys.iters = 0;
	else if (keycode == KEY_ARROWLEFT || keycode == KEY_ARROWRIGHT)
		data->keys.x_move = 0;
	else if (keycode == KEY_ARROWUP || keycode == KEY_ARROWDOWN)
		data->keys.y_move = 0;
	return (0);
}

static void	handle_mouse_left(t_data *data, int x, int y)
{
	if (x >= data->winsize.width - FRACT_PREVIEWS_WIDTH
			&& y <= FRACT_PREVIEWS * FRACT_PREVIEWS_HEIGHT)
		change_fract_type(data
				, (int)ceil(y / (double)FRACT_PREVIEWS_HEIGHT) - 1);
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
		real_x = (x + data->cam.x_off) * (data->cam.x_max - data->cam.x_min)
			/ data->winsize.width + data->cam.x_min;
		real_y = (y + data->cam.y_off) * (data->cam.y_max - data->cam.y_min)
			/ data->winsize.height + data->cam.y_min;
		data->cam.x_min = real_x - (real_x - data->cam.x_min) * data->cam.scale;
		data->cam.x_max = real_x - (real_x - data->cam.x_max) * data->cam.scale;
		data->cam.y_min = real_y - (real_y - data->cam.y_min) * data->cam.scale;
		data->cam.y_max = real_y - (real_y - data->cam.y_max) * data->cam.scale;
		if (data->not_epileptic)
			data->color_mul += 2;
		redraw_all(data);
	}
	return (0);
}

int			motion_hook(int x, int y, t_data *data)
{
	if (data->motion.record)
	{
		data->motion.x = (x + data->cam.x_off)
			* (data->cam.x_max - data->cam.x_min)
			/ data->winsize.width + data->cam.x_min;
		data->motion.y = (y + data->cam.y_off)
			* (data->cam.y_max - data->cam.y_min)
			/ data->winsize.height + data->cam.y_min;
		if (data->fract_fn == julia)
			data->draw_fn(data);
		draw_preview(data, &data->previews[0], julia);
		expose_hook(data);
	}
	return (0);
}
