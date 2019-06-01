/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix44.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 16:01:53 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/01 20:00:41 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
