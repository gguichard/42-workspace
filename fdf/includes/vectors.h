/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 16:32:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/12 17:29:22 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct	s_vec2d
{
	double		x;
	double		y;
}				t_vec2d;

typedef struct	s_vec3d
{
	double		x;
	double		y;
	double		z;
}				t_vec3d;

t_vec2d			vec2d(double x, double y);

t_vec3d			vec3d(double x, double y, double z);
t_vec3d			vec3d_add(t_vec3d vec_1, t_vec3d vec_2);
t_vec3d			vec3d_sub(t_vec3d vec_1, t_vec3d vec_2);
t_vec3d			vec3d_scalar(t_vec3d vector, double scalar);

#endif
