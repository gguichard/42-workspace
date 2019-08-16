/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 16:32:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/08/16 13:34:11 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct	s_vec3d
{
	double		x;
	double		y;
	double		z;
}				t_vec3d;

t_vec3d			vec3d(double x, double y, double z);

#endif
