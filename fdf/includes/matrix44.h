/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix44.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 16:18:04 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/02 20:17:25 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX44_H
# define MATRIX44_H

# include "vectors.h"

void	mat44_identity(double mat[4][4]);
void	mat44_mul(double mat_a[4][4], double mat_b[4][4], double result[4][4]);
t_vec3d	mat44_apply(double mat[4][4], t_vec3d v);
void	mat44_rotation(double rot_mat[4][4], double angle, char axis);
void	mat44_scale(double mat[4][4], double x, double y, double z);

#endif
