/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 04:37:08 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/11 04:37:20 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int get_fract_color(int iters)
{
	int colors[] = {
		0x421e0f, 0x19071a, 0x09012f, 0x040449,
		0x000764, 0x022c8a, 0x1852b1, 0x397dd1,
		0x86b5e5, 0xd3ecf8, 0xf1e9bf, 0xf8c95f,
		0xffaa00, 0xcc8000, 0x995700, 0x6a3403
	};
	return (colors[iters % 16]);
}

__kernel void julia(__global int *data, int color_mul, int x_off, int y_off
		, double x_min, double x_max, double y_min, double y_max
		, int width, int height, int max_iters
		, double motion_x, double motion_y)
{
	int id = get_global_id(0);
	double x = (id % width + x_off) * (x_max - x_min) / width + x_min;
	double y = (id / width + y_off) * (y_max - y_min) / height + y_min;
	double x_tmp = 0.0;
	double x2 = x * x;
	double y2 = y * y;
	int	iters = 0;
	while (iters < max_iters && (x2 + y2) < 4)
	{
		x_tmp = x;
		x = x2 - y2 + motion_x;
		y = 2 * x_tmp * y + motion_y;
		x2 = x * x;
		y2 = y * y;
		iters++;
	}
	data[id] = (iters == max_iters) ? 0 : get_fract_color(iters) * color_mul;
}

__kernel void mandelbrot(__global int *data, int color_mul, int x_off, int y_off
		, double x_min, double x_max, double y_min, double y_max
		, int width, int height, int max_iters
		, double motion_x, double motion_y)
{
	int id = get_global_id(0);
	double re = (id % width + x_off) * (x_max - x_min) / width + x_min;
	double im = (id / width + y_off) * (y_max - y_min) / height + y_min;
	double x = 0.0;
	double y = 0.0;
	double x_tmp = 0.0;
	double x2 = 0.0;
	double y2 = 0.0;
	int	iters = 0;
	while (iters < max_iters)
	{
		x2 = x * x;
		y2 = y * y;
		if (x2 + y2 >= 4)
			break;
		x_tmp = x;
		x = x2 - y2 + re;
		y = 2 * x_tmp * y + im;
		iters++;
	}
	data[id] = (iters == max_iters) ? 0 : get_fract_color(iters) * color_mul;
}

__kernel void mandelbar(__global int *data, int color_mul, int x_off, int y_off
		, double x_min, double x_max, double y_min, double y_max
		, int width, int height, int max_iters
		, double motion_x, double motion_y)
{
	int id = get_global_id(0);
	double re = (id % width + x_off) * (x_max - x_min) / width + x_min;
	double im = (id / width + y_off) * (y_max - y_min) / height + y_min;
	double x = 0.0;
	double y = 0.0;
	double x_tmp = 0.0;
	double x2 = 0.0;
	double y2 = 0.0;
	int	iters = 0;
	while (iters < max_iters)
	{
		x2 = x * x;
		y2 = y * y;
		if (x2 + y2 >= 4)
			break;
		x_tmp = x;
		x = x2 - y2 + re;
		y = -2 * x_tmp * y + im;
		iters++;
	}
	data[id] = (iters == max_iters) ? 0 : get_fract_color(iters) * color_mul;
}

__kernel void burning_ship(__global int *data, int color_mul
		, int x_off, int y_off
		, double x_min, double x_max, double y_min, double y_max
		, int width, int height, int max_iters
		, double motion_x, double motion_y)
{
	int id = get_global_id(0);
	double re = (id % width + x_off) * (x_max - x_min) / width + x_min;
	double im = (id / width + y_off) * (y_max - y_min) / height + y_min;
	double x = 0.0;
	double y = 0.0;
	double x_tmp = 0.0;
	double x2 = 0.0;
	double y2 = 0.0;
	int	iters = 0;
	while (iters < max_iters)
	{
		x2 = x * x;
		y2 = y * y;
		if (x2 + y2 >= 4)
			break;
		x_tmp = x;
		x = fabs(x2 - y2 + re);
		y = fabs(2 * x_tmp * y) + im;
		iters++;
	}
	data[id] = (iters == max_iters) ? 0 : get_fract_color(iters) * color_mul;
}
