/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 16:41:40 by gguichar          #+#    #+#             */
/*   Updated: 2019/08/16 13:33:57 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec3d	vec3d(double x, double y, double z)
{
	t_vec3d	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}
