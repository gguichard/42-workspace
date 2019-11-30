/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2d_ope.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 13:25:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/30 13:25:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"

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
