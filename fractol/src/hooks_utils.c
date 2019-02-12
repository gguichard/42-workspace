/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 09:01:12 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/12 09:01:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	reset_draw(t_data *data)
{
	data->cam.x_min = -2.0;
	data->cam.x_max = 2.0;
	data->cam.y_min = -2.0;
	data->cam.y_max = 2.0;
	data->cam.scale = 1.0;
	data->max_iters = 100;
	data->draw_fn(data);
	expose_hook(data);
}

void	change_fract_type(t_data *data, int idx)
{
	void	*new_fract_fn;

	new_fract_fn = get_preview_draw_fn(idx);
	if (data->use_opencl && new_fract_fn != data->fract_fn)
	{
		release_opencl(data);
		setup_opencl(data);
	}
	data->fract_fn = new_fract_fn;
	reset_draw(data);
}
