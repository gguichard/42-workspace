/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 20:56:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/01 20:16:31 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#include "keys.h"

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

	scale = fdf->cam.scale;
	if (fdf->keys & SCALE_OUT)
		scale *= 1.1;
	if (fdf->keys & SCALE_IN)
		scale /= 1.1;
	if (scale > 1.)
		scale = 1.;
	if (scale == fdf->cam.scale)
		return (0);
	fdf->cam.scale = scale;
	return (1);
}

int	handle_depth(t_fdf *fdf)
{
	double	tmp;

	tmp = fdf->cam.depth;
	if (fdf->keys & DEPTH_DECREASE)
		tmp -= .1;
	if (fdf->keys & DEPTH_INCREASE)
		tmp += .1;
	if (tmp == fdf->cam.depth)
		return (0);
	fdf->cam.depth = tmp;
	return (1);
}

int	handle_angle(t_fdf *fdf)
{
	int		angle;
	double	rad;

	angle = fdf->cam.angle;
	if (fdf->keys & ROTATE_LEFT)
		angle -= 5;
	if (fdf->keys & ROTATE_RIGHT)
		angle += 5;
	if (angle == fdf->cam.angle)
		return (0);
	fdf->cam.angle = angle % 360;
	rad = fdf->cam.angle * M_PI / 180.0;
	fdf->cam.angle_sin = sin(rad);
	fdf->cam.angle_cos = cos(rad);
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
