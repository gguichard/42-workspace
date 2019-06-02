/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 20:56:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/02 14:29:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "fdf.h"
#include "keys.h"
#include "matrix44.h"

int	handle_move(t_fdf *fdf)
{
	if (fdf->keys & TRANSLATE_X_LEFT)
		fdf->matrix[3][0] += 8;
	if (fdf->keys & TRANSLATE_X_RIGHT)
		fdf->matrix[3][0] -= 8;
	if (fdf->keys & TRANSLATE_Y_UP)
		fdf->matrix[3][1] += 8;
	if (fdf->keys & TRANSLATE_Y_DOWN)
		fdf->matrix[3][1] -= 8;
	return (fdf->keys & TRANSLATE_X_LEFT || fdf->keys & TRANSLATE_X_RIGHT
		|| fdf->keys & TRANSLATE_Y_UP || fdf->keys & TRANSLATE_Y_DOWN);
}

int	handle_scale(t_fdf *fdf)
{
	double	scale;

	scale = fdf->matrix[3][3];
	if (fdf->keys & SCALE_OUT)
		scale *= 1.1;
	if (fdf->keys & SCALE_IN)
		scale /= 1.1;
	scale = clamp(scale, 0, 1);
	if (scale == fdf->matrix[3][3])
		return (0);
	fdf->matrix[3][3] = scale;
	return (1);
}

int	handle_depth(t_fdf *fdf)
{
	double	depth;

	depth = fdf->matrix[2][2];
	if (fdf->keys & DEPTH_DECREASE)
		depth *= 1.1;
	if (fdf->keys & DEPTH_INCREASE)
		depth /= 1.1;
	depth = clamp(depth, 0, 1);
	if (depth == fdf->matrix[2][2])
		return (0);
	fdf->matrix[2][2] = depth;
	return (1);
}

int	handle_rotation(t_fdf *fdf, char axis)
{
	int		angle;

	angle = 0;
	if (fdf->keys & ROTATE_LEFT)
		angle += 5;
	if (fdf->keys & ROTATE_RIGHT)
		angle -= 5;
	if (angle == 0)
		return (0);
	rotate_with_mat(fdf, angle, axis);
	return (1);
}
