/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:11:27 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/10 12:29:54 by gguichar         ###   ########.fr       */
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

t_vec2d	vec2d_add(t_vec2d a, t_vec2d b)
{
	a.x += b.x;
	a.y += b.y;
	return (a);
}

t_vec2d	vec2d_sub(t_vec2d a, t_vec2d b)
{
	a.x -= b.x;
	a.y -= b.y;
	return (a);
}

t_vec2d	vec2d_mulf(t_vec2d a, double scalar)
{
	a.x *= scalar;
	a.y *= scalar;
	return (a);
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
