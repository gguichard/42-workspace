/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:11:27 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/30 13:25:41 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec2.h"

t_vec2d	vec2d(double x, double y)
{
	t_vec2d	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

double	vec2d_length2(t_vec2d a)
{
	return (a.x * a.x + a.y * a.y);
}

t_vec2d	vec2d_unit(t_vec2d a)
{
	double	length;

	length = sqrt(a.x * a.x + a.y * a.y);
	a.x /= length;
	a.y /= length;
	return (a);
}

t_vec2d	vec2d_rotate(t_vec2d a, double angle)
{
	t_vec2d	cossin;

	cossin = vec2d(cos(angle), -sin(angle));
	return (vec2d(a.x * cossin.x - a.y * cossin.y
		, a.x * cossin.y + a.y * cossin.x));
}
