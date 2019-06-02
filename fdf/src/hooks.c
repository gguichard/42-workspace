/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 04:05:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/02 21:32:50 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include "fdf.h"
#include "vectors.h"
#include "matrix44.h"

int		expose_hook(t_fdf *fdf)
{
	mlx_put_image_to_window(fdf->lib.mlx_ptr
		, fdf->lib.win_ptr
		, fdf->lib.img_ptr
		, 0, 0);
	return (0);
}

int		loop_hook(t_fdf *fdf)
{
	if (handle_move(fdf) | handle_scale(fdf)
		| handle_depth(fdf) | handle_rotation(fdf, 'z'))
	{
		fill_window_image(fdf);
		expose_hook(fdf);
	}
	return (0);
}

void	rotate_with_mat(t_fdf *fdf, int delta, char axis)
{
	double	angle;
	double	rot_mat[4][4];
	double	final_mat[4][4];

	angle = delta / 180. * M_PI;
	mat44_rotation(rot_mat, angle, axis);
	mat44_mul(fdf->matrix, rot_mat, final_mat);
	ft_memcpy(fdf->matrix, final_mat, sizeof(final_mat));
}

int		motion_hook(int x, int y, t_fdf *fdf)
{
	t_vec2d	delta;

	if (fdf->drag)
	{
		delta = vec2d(x - fdf->prev_cursor.x, y - fdf->prev_cursor.y);
		if (delta.x != 0)
			rotate_with_mat(fdf, delta.x, 'y');
		if (delta.y != 0)
			rotate_with_mat(fdf, -delta.y, 'x');
		if (delta.x != 0 || delta.y != 0)
		{
			fill_window_image(fdf);
			expose_hook(fdf);
		}
		fdf->prev_cursor = vec2d(x, y);
	}
	return (0);
}
