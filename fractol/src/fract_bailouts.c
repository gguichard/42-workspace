/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_bailouts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 03:03:44 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/12 03:05:59 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fractol.h"

int	fract_bailout(double x, double y, double re, double im
		, int max_iters)
{
	int		iters;
	double	x2;
	double	y2;
	double	x_tmp;

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

int	fract_bailout_2(double x, double y, double re, double im
		, int max_iters)
{
	int		iters;
	double	x2;
	double	y2;
	double	x_tmp;

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

int	fract_invert_bailout(double x, double y, double re, double im
		, int max_iters)
{
	int		iters;
	double	x2;
	double	y2;
	double	x_tmp;

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
