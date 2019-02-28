/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 09:01:12 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/28 12:01:39 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	redraw_all(t_data *data)
{
	data->draw_fn(data);
	expose_hook(data);
}

void	reset_draw(t_data *data)
{
	data->not_epileptic = 0;
	data->sampling = 1;
	data->color_mul = 1;
	data->cam.x_off = 0;
	data->cam.y_off = 0;
	data->cam.x_min = -2.0;
	data->cam.x_max = 2.0;
	data->cam.y_min = -2.0;
	data->cam.y_max = 2.0;
	data->cam.scale = 1.0;
	data->max_iters = 100;
	redraw_all(data);
}

void	change_fract_type(t_data *data, int idx)
{
	void	*old_fract_fn;

	if (idx < 0)
		idx = FRACT_PREVIEWS - 1;
	if (idx >= FRACT_PREVIEWS)
		idx = 0;
	old_fract_fn = data->fract_fn;
	data->fract_fn = get_preview_draw_fn(idx);
	if (data->use_opencl && old_fract_fn != data->fract_fn)
	{
		release_opencl(data);
		setup_opencl(data);
	}
	data->preview_idx = idx;
	reset_draw(data);
}

void	increase_sampling(t_data *data)
{
	data->sampling *= 2;
	if (data->sampling > 4)
		data->sampling = 1;
	redraw_all(data);
}
