/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 11:53:46 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/12 04:27:48 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "libft.h"
#include "fractol.h"
#include "keys.h"

int	expose_hook(t_data *data)
{
	mlx_put_image_to_window(data->lib.mlx_ptr
			, data->lib.win_ptr
			, data->lib.img_ptr
			, 0, 0);
	return (0);
}

int	loop_hook(t_data *data)
{
	if (data->keys.iters != 0)
	{
		data->max_iters += data->keys.iters;
		if (data->max_iters < 0)
			data->max_iters = 0;
		else if (data->max_iters > 1000)
			data->max_iters = 1000;
		data->draw_fn(data);
		expose_hook(data);
	}
	return (0);
}

int	exit_lib(t_data *data)
{
	if (data->use_opencl)
		release_opencl(data);
	destroy_mlx(&(data->lib));
	exit(0);
	return (0);
}
