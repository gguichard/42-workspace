/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 16:41:40 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/12 17:29:06 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec2d	vec2d(double x, double y)
{
	t_vec2d	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_vec3d	vec3d(double x, double y, double z)
{
	t_vec3d	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3d	vec3d_add(t_vec3d vec_1, t_vec3d vec_2)
{
	t_vec3d	vec;

	vec.x = vec_1.x + vec_2.x;
	vec.y = vec_1.y + vec_2.y;
	vec.z = vec_1.z + vec_2.z;
	return (vec);
}

t_vec3d	vec3d_sub(t_vec3d vec_1, t_vec3d vec_2)
{
	t_vec3d	vec;

	vec.x = vec_1.x - vec_2.x;
	vec.y = vec_1.y - vec_2.y;
	vec.z = vec_1.z - vec_2.z;
	return (vec);
}

t_vec3d	vec3d_scalar(t_vec3d vector, double scalar)
{
	return (vec3d(vector.x * scalar, vector.y * scalar, vector.z * scalar));
}
