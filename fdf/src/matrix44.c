/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix44.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 16:01:53 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/02 21:39:09 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "vectors.h"

void	mat44_identity(double mat[4][4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mat[i][j] = (i == j);
			j++;
		}
		i++;
	}
}

void	mat44_mul(double mat_a[4][4], double mat_b[4][4], double result[4][4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result[i][j] = mat_a[i][0] * mat_b[0][j]
				+ mat_a[i][1] * mat_b[1][j]
				+ mat_a[i][2] * mat_b[2][j]
				+ mat_a[i][3] * mat_b[3][j];
			j++;
		}
		i++;
	}
}

t_vec3d	mat44_apply(double mat[4][4], t_vec3d v)
{
	t_vec3d	v2;
	double	w;

	v2.x = v.x * mat[0][0] + v.y * mat[1][0] + v.z * mat[2][0] + mat[3][0];
	v2.y = v.x * mat[0][1] + v.y * mat[1][1] + v.z * mat[2][1] + mat[3][1];
	v2.z = v.x * mat[0][2] + v.y * mat[1][2] + v.z * mat[2][2] + mat[3][2];
	w = v.x * mat[0][3] + v.y * mat[1][3] + v.z * mat[2][3] + mat[3][3];
	if (w != 0. && w != 1.)
		return (vec3d_scalar(v2, 1 / w));
	else
		return (v2);
}

void	mat44_rotation(double rot_mat[4][4], double angle, char axis)
{
	mat44_identity(rot_mat);
	if (axis == 'x')
	{
		rot_mat[1][1] = cos(angle);
		rot_mat[2][2] = rot_mat[1][1];
		rot_mat[1][2] = sin(angle);
		rot_mat[2][1] = -rot_mat[1][2];
	}
	else if (axis == 'y')
	{
		rot_mat[0][0] = cos(angle);
		rot_mat[2][2] = rot_mat[0][0];
		rot_mat[2][0] = sin(angle);
		rot_mat[0][2] = -rot_mat[2][0];
	}
	else if (axis == 'z')
	{
		rot_mat[0][0] = cos(angle);
		rot_mat[1][1] = rot_mat[0][0];
		rot_mat[0][1] = sin(angle);
		rot_mat[1][0] = -rot_mat[0][1];
	}
}

void	mat44_scale(double mat[4][4], t_vec3d v)
{
	double	scale_mat[4][4];
	double	result[4][4];

	mat44_identity(scale_mat);
	scale_mat[0][0] = v.x;
	scale_mat[1][1] = v.y;
	scale_mat[2][2] = v.z;
	mat44_mul(scale_mat, mat, result);
	ft_memcpy(mat, result, sizeof(result));
}
