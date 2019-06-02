/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 20:56:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/02 12:51:19 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "fdf.h"
#include "keys.h"
#include "matrix44.h"

int	handle_move(t_fdf *fdf)
{
	t_cam	cam;

	cam = fdf->cam;
	if (fdf->keys & TRANSLATE_X_LEFT)
		fdf->cam.origin.x += 10;
	if (fdf->keys & TRANSLATE_X_RIGHT)
		fdf->cam.origin.x -= 10;
	if (fdf->keys & TRANSLATE_Y_UP)
		fdf->cam.origin.y += 10;
	if (fdf->keys & TRANSLATE_Y_DOWN)
		fdf->cam.origin.y -= 10;
	return (fdf->cam.origin.x != cam.origin.x
		|| fdf->cam.origin.y != cam.origin.y);
}

int	handle_scale(t_fdf *fdf)
{
	double	scale;

	scale = fdf->matrix[3][3];
	if (fdf->keys & SCALE_OUT)
		scale *= 1.1;
	if (fdf->keys & SCALE_IN)
		scale /= 1.1;
	if (scale > 1.)
		scale = 1.;
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
	if (depth > 1.)
		depth = 1.;
	if (depth != fdf->matrix[2][2])
		return (0);
	fdf->matrix[2][2] = depth;
	return (1);
}

int	handle_rotation(t_fdf *fdf, char axis)
{
	double	angle;
	double	rot_mat[4][4];
	double	final_mat[4][4];

	angle = .0;
	if (fdf->keys & ROTATE_LEFT)
		angle += 5;
	if (fdf->keys & ROTATE_RIGHT)
		angle -= 5;
	if (angle == .0)
		return (0);
	angle = angle / 180 * M_PI;
	mat44_rotation(rot_mat, angle, axis);
	mat44_mul(fdf->matrix, rot_mat, final_mat);
	ft_memcpy(fdf->matrix, final_mat, sizeof(final_mat));
	return (1);
}

int	handle_proj(t_fdf *fdf, int keycode)
{
	if (keycode == KEY_I)
		fdf->proj = e_iso;
	else if (keycode == KEY_P)
		fdf->proj = e_parallel;
	return (1);
}
