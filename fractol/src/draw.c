/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 00:47:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/10 06:45:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fractol.h"

static int	get_fract_color(int iters)
{
	static int	colors[] = {
		0x421e0f,
		0x19071a,
		0x09012f,
		0x040449,
		0x000764,
		0x022c8a,
		0x1852b1,
		0x397dd1,
		0x86b5e5,
		0xd3ecf8,
		0xf1e9bf,
		0xf8c95f,
		0xffaa00,
		0xcc8000,
		0x995700,
		0x6a3403
	};

	return (colors[iters % 16]);
}

void		draw_fractal(t_data *data)
{
	int		x;
	int		y;
	double	re;
	double	im;
	int		iters;

	ft_memset(data->lib.img_data, 0, data->lib.size_line * data->winsize.height);
	x = 0;
	while (x < data->winsize.width)
	{
		y = 0;
		while (y < data->winsize.height)
		{
			re = (x - data->winsize.width / 2.0) * 4.0 * data->cam.scale / data->winsize.width;
			im = (y - data->winsize.height / 2.0) * 4.0 * data->cam.scale / data->winsize.height;
			iters = data->fract_fn(&data->motion, re, im, data->max_iters);
			data->lib.img_data[y * data->winsize.width + x] =
				iters < data->max_iters ? get_fract_color(iters) : 0;
			y++;
		}
		x++;
	}
}
