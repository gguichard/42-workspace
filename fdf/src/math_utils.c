/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 03:44:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/01/01 03:49:03 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		lint(int start, int end, double percent)
{
	return (int)((1 - percent) * start + percent * end);
}

double	pcnt(int start, int end, int current)
{
	double	dist;

	dist = end - start;
	if (dist == 0)
		return (1.0);
	return ((current - start) / dist);
}

int		get_color(t_pos start, t_pos end, double percent)
{
	int		r;
	int		g;
	int		b;

	if (start.color == end.color)
		return (start.color);
	if (percent == 0)
		return (start.color);
	if (percent == 1)
		return (end.color);
	r = lint((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percent);
	g = lint((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percent);
	b = lint(start.color & 0xFF, end.color & 0xFF, percent);
	return ((r << 16) | (g << 8) | b);
}
