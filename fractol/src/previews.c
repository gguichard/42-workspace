/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   previews.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 07:38:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/12 10:07:11 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fractol.h"

void	*get_preview_draw_fn(int idx)
{
	static void	*previews_fn[FRACT_PREVIEWS] = {
		julia,
		mandelbrot,
		mandelbar,
		burning_ship
	};

	return (previews_fn[idx]);
}

void	draw_preview(t_data *data, t_mlximg *img
		, int (*fract_fn)(t_motion *, double, double, int))
{
	int	x;
	int	y;
	int	iters;
	int	color;

	x = -1;
	while (++x < img->size.width)
	{
		y = -1;
		while (++y < img->size.height)
		{
			if (x == 0 || (y + 1) == img->size.height)
				color = 0xD3D3D3;
			else
			{
				iters = fract_fn(&data->motion
						, x * 4.0 / img->size.width - 2.0
						, y * 4.0 / img->size.height - 2.0
						, FRACT_PREVIEWS_MAXITERS);
				color = (iters < FRACT_PREVIEWS_MAXITERS)
					? get_fract_color(iters) : 0;
			}
			img->data[y * img->size.width + x] = color | 0x20000000;
		}
	}
}

void	destroy_previews(t_data *data)
{
	int			idx;
	t_mlximg	*preview;

	idx = 0;
	while (idx < FRACT_PREVIEWS)
	{
		preview = &data->previews[idx];
		if (preview->ptr != NULL)
		{
			mlx_destroy_image(data->lib.mlx_ptr, preview->ptr);
			ft_memset(preview, 0, sizeof(t_mlximg));
		}
		idx++;
	}
}

int		init_previews(t_data *data)
{
	int			idx;
	t_winsize	size;

	idx = 0;
	size.width = FRACT_PREVIEWS_WIDTH;
	size.height = FRACT_PREVIEWS_HEIGHT;
	while (idx < FRACT_PREVIEWS)
	{
		if (!create_mlximage(&data->lib, size, &data->previews[idx]))
		{
			destroy_previews(data);
			return (0);
		}
		draw_preview(data, &data->previews[idx], get_preview_draw_fn(idx));
		idx++;
	}
	return (1);
}
