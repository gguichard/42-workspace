/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 12:10:06 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/10 04:33:11 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "motion.h"
#include "fractol.h"

int	julia(t_motion *motion, double re, double im, int max_iters)
{
	double	x;
	double	y;
	double	x_tmp;
	double	iters;

	x = re;
	y = im;
	iters = 0;
	while (iters < max_iters && (x * x + y * y) <= 4)
	{
		x_tmp = x;
		x = x * x - y * y + motion->x;//0.285;
		y = 2 * x_tmp * y + motion->y;//0.01;
		iters++;
	}
	return (iters);
}

int	mandelbrot(t_motion *motion, double re, double im, int max_iters)
{
	double	x;
	double	y;
	double	x_tmp;
	int		iters;

	(void)motion;
	x = 0;
	y = 0;
	iters = 0;
	while (iters < max_iters && (x * x + y * y) <= 4)
	{
		x_tmp = x;
		x = x * x - y * y + re;
		y = 2 * x_tmp * y + im;
		iters++;
	}
	return (iters);
}
