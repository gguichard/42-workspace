/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:14:59 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/31 17:38:26 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_H
# define VEC2_H

typedef struct	s_vec2i
{
	int			x;
	int			y;
}				t_vec2i;

typedef struct	s_vec2d
{
	double		x;
	double		y;
}				t_vec2d;

t_vec2i			vec2i(int x, int y);

t_vec2d			vec2d(double x, double y);
t_vec2d			vec2d_add(t_vec2d a, t_vec2d b);
t_vec2d			vec2d_sub(t_vec2d a, t_vec2d b);
t_vec2d			vec2d_scalar(t_vec2d a, double scalar);
double			vec2d_length2(t_vec2d a);
t_vec2d			vec2d_unit(t_vec2d a);

#endif
