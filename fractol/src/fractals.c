/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 12:10:06 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/12 02:15:56 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "motion.h"
#include "fractol.h"

static int	fract_bailout(double x, double y, double re, double im
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

static int	invert_fract_bailout(double x, double y, double re, double im
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

int			julia(t_motion *motion, double re, double im, int max_iters)
{
	return (fract_bailout(re, im, motion->x, motion->y, max_iters));
}

int			mandelbrot(t_motion *motion, double re, double im, int max_iters)
{
	(void)motion;
	return (fract_bailout(0, 0, re, im, max_iters));
}

int			mandelbar(t_motion *motion, double re, double im, int max_iters)
{
	(void)motion;
	return (invert_fract_bailout(0, 0, re, im, max_iters));
}
