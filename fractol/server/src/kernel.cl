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

#define JULIA 0
#define MANDELBROT 1
#define MANDELBAR 2
#define BURNING_SHIP 3

int	fract_bailout(double x, double y, double re, double im, int max_iters)
{
	int		iters;
	double	x2;
	double	y2;
	double	x_tmp = 0.0;

	iters = 0;
	while (iters < max_iters)
	{
		x2 = x * x;
		y2 = y * y;
		if (x2 + y2 >= 4)
			break ;
		x_tmp = x;
		x = x2 - y2 + re;
		y = 2 * x_tmp * y + im;
		iters++;
	}
	return (iters);
}

int	fract_bailout_2(double x, double y, double re, double im, int max_iters)
{
	int		iters;
	double	x2;
	double	y2;
	double	x_tmp = 0.0;

	iters = 0;
	while (iters < max_iters)
	{
		x2 = x * x;
		y2 = y * y;
		if (x2 + y2 >= 4)
			break ;
		x_tmp = x;
		x = fabs(x2 - y2 + re);
		y = fabs(2 * x_tmp * y) + im;
		iters++;
	}
	return (iters);
}

int	fract_inv_bailout(double x, double y, double re, double im, int max_iters)
{
	int		iters;
	double	x2;
	double	y2;
	double	x_tmp = 0.0;

	iters = 0;
	while (iters < max_iters)
	{
		x2 = x * x;
		y2 = y * y;
		if (x2 + y2 >= 4)
			break ;
		x_tmp = x;
		x = x2 - y2 + re;
		y = -2 * x_tmp * y + im;
		iters++;
	}
	return (iters);
}

__kernel void draw_fractal(__global int *data, int type, int width, int height
		, int x_off, int y_off, double x_min, double x_max, double y_min, double y_max
		, double motion_x, double motion_y, int max_iters)
{
	int		id;
	double	re;
	double	im;
	int		iters;

	id = get_global_id(0);
	re = (id % width + x_off) * (x_max - x_min) / width + x_min;
	im = (id / width + y_off) * (y_max - y_min) / height + y_min;
	switch (type)
	{
		case JULIA:
			iters = fract_bailout(re, im, motion_x, motion_y, max_iters);
			break ;
		case MANDELBROT:
			iters = fract_bailout(0, 0, re, im, max_iters);
			break ;
		case MANDELBAR:
			iters = fract_inv_bailout(0, 0, re, im, max_iters);
			break ;
		case BURNING_SHIP:
			iters = fract_bailout_2(0, 0, re, im, max_iters);
			break ;
	}
	return ((iters == max_iters) ? 0 : get_fract_color(iters));
}
