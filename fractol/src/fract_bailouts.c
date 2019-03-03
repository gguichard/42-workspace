/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_bailouts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 03:03:44 by gguichar          #+#    #+#             */
/*   Updated: 2019/03/03 19:07:54 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fractol.h"

int	fract_bailout(t_point point, double re, double im, int max_iters)
{
	int		iters;
	double	x2;
	double	y2;
	double	x_tmp;

	iters = 0;
	while (iters < max_iters)
	{
		x2 = point.x * point.x;
		y2 = point.y * point.y;
		if (x2 + y2 >= 4)
			break ;
		x_tmp = point.x;
		point.x = x2 - y2 + re;
		point.y = 2 * x_tmp * point.y + im;
		iters++;
	}
	return (iters);
}

int	fract_bailout_2(t_point point, double re, double im, int max_iters)
{
	int		iters;
	double	x2;
	double	y2;
	double	x_tmp;

	iters = 0;
	while (iters < max_iters)
	{
		x2 = point.x * point.x;
		y2 = point.y * point.y;
		if (x2 + y2 >= 4)
			break ;
		x_tmp = point.x;
		point.x = fabs(x2 - y2 + re);
		point.y = fabs(2 * x_tmp * point.y) + im;
		iters++;
	}
	return (iters);
}

int	fract_inv_bailout(t_point point, double re, double im, int max_iters)
{
	int		iters;
	double	x2;
	double	y2;
	double	x_tmp;

	iters = 0;
	while (iters < max_iters)
	{
		x2 = point.x * point.x;
		y2 = point.y * point.y;
		if (x2 + y2 >= 4)
			break ;
		x_tmp = point.x;
		point.x = x2 - y2 + re;
		point.y = -2 * x_tmp * point.y + im;
		iters++;
	}
	return (iters);
}
