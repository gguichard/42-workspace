/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 11:53:46 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/12 10:34:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "libft.h"
#include "fractol.h"
#include "keys.h"

static void	draw_previews(t_data *data)
{
	int			idx;
	int			preview_hoff;
	t_mlximg	*preview;

	idx = 0;
	preview_hoff = 0;
	while (idx < FRACT_PREVIEWS)
	{
		preview = &data->previews[idx];
		mlx_put_image_to_window(data->lib.mlx_ptr, data->lib.win_ptr
				, preview->ptr
				, data->winsize.width - preview->size.width, preview_hoff);
		preview_hoff += preview->size.height;
		idx++;
	}
	draw_selected_preview(data);
}

int			expose_hook(t_data *data)
{
	char	*str;

	mlx_put_image_to_window(data->lib.mlx_ptr
			, data->lib.win_ptr
			, data->lib.img_ptr
			, 0, 0);
	if (data->keys.show_hud)
		draw_previews(data);
	ft_asprintf(&str, "Iterations: %d", data->max_iters);
	if (str != NULL)
	{
		mlx_string_put(data->lib.mlx_ptr, data->lib.win_ptr
				, 50, data->winsize.height - 50, 0xFFFFFF
				, str);
		free(str);
	}
	return (0);
}

int			loop_hook(t_data *data)
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

int			exit_lib(t_data *data)
{
	if (data->use_opencl)
		release_opencl(data);
	destroy_previews(data);
	destroy_mlx(&(data->lib));
	exit(0);
	return (0);
}
