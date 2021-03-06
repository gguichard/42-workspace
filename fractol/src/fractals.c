/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 12:10:06 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/12 05:21:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "motion.h"
#include "fractol.h"

int	julia(t_motion *motion, double re, double im, int max_iters)
{
	return (fract_bailout((t_point){re, im}, motion->x, motion->y, max_iters));
}

int	mandelbrot(t_motion *motion, double re, double im, int max_iters)
{
	(void)motion;
	return (fract_bailout((t_point){0, 0}, re, im, max_iters));
}

int	mandelbar(t_motion *motion, double re, double im, int max_iters)
{
	(void)motion;
	return (fract_inv_bailout((t_point){0, 0}, re, im, max_iters));
}

int	burning_ship(t_motion *motion, double re, double im, int max_iters)
{
	(void)motion;
	return (fract_bailout_2((t_point){0, 0}, re, im, max_iters));
}
