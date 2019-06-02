/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 03:44:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/02 14:28:47 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double			clamp(double value, double lo, double hi)
{
	if (value < lo)
		return (lo);
	else if (value > hi)
		return (hi);
	else
		return (value);
}

int				lint(int start, int end, double percent)
{
	return (int)((1 - percent) * start + percent * end);
}

double			pcnt(int start, int end, int current)
{
	double	dist;

	dist = end - start;
	if (dist == 0)
		return (1.);
	return ((current - start) / dist);
}

unsigned int	get_color(unsigned int start, unsigned int end, double percent)
{
	int		r;
	int		g;
	int		b;

	if (percent == 0. || start == end)
		return (start);
	if (percent == 1.)
		return (end);
	r = lint((start >> 16) & 0xFF, (end >> 16) & 0xFF, percent);
	g = lint((start >> 8) & 0xFF, (end >> 8) & 0xFF, percent);
	b = lint(start & 0xFF, end & 0xFF, percent);
	return ((r << 16) | (g << 8) | b);
}
