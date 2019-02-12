/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   previews.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 07:38:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/13 00:37:22 by gguichar         ###   ########.fr       */
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

void	draw_selected_preview(t_data *data)
{
	int	x;
	int	y;

	x = data->winsize.width - FRACT_PREVIEWS_WIDTH;
	y = data->preview_idx * FRACT_PREVIEWS_HEIGHT - 1;
	while (x < data->winsize.width)
	{
		if (y > 0)
			mlx_pixel_put(data->lib.mlx_ptr, data->lib.win_ptr, x, y
					, FRACT_PREVIEWS_COLOR);
		mlx_pixel_put(data->lib.mlx_ptr, data->lib.win_ptr, x
				, y + FRACT_PREVIEWS_HEIGHT, FRACT_PREVIEWS_COLOR);
		x++;
	}
	x = data->winsize.width - FRACT_PREVIEWS_WIDTH;
	y = data->preview_idx * FRACT_PREVIEWS_HEIGHT - 1;
	while (y < (data->preview_idx + 1) * FRACT_PREVIEWS_HEIGHT)
	{
		mlx_pixel_put(data->lib.mlx_ptr, data->lib.win_ptr, x, y
				, FRACT_PREVIEWS_COLOR);
		mlx_pixel_put(data->lib.mlx_ptr, data->lib.win_ptr
				, x + FRACT_PREVIEWS_WIDTH - 1, y, FRACT_PREVIEWS_COLOR);
		y++;
	}
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
				color = 0x606060;
			else
			{
				iters = fract_fn(&data->motion
						, x * 4.0 / img->size.width - 2.0
						, y * 4.0 / img->size.height - 2.0
						, FRACT_PREVIEWS_MAXITERS);
				color = (iters < FRACT_PREVIEWS_MAXITERS)
					? 0xA0000000 : 0x80FFFFFF;
			}
			img->data[y * img->size.width + x] = color;
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
	void		*fract_fn;

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
		fract_fn = get_preview_draw_fn(idx);
		if (fract_fn == data->fract_fn)
			data->preview_idx = idx;
		draw_preview(data, &data->previews[idx], fract_fn);
		idx++;
	}
	return (1);
}
