/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 20:56:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/01/01 04:12:09 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

int	handle_move(t_fdf *fdf)
{
	if (fdf->move.x != 0)
		fdf->cam.x += fdf->move.x * fdf->scale;
	if (fdf->move.y != 0)
		fdf->cam.y += fdf->move.y * fdf->scale;
	return (fdf->move.x != 0 || fdf->move.y != 0);
}

int	handle_scale(t_fdf *fdf)
{
	int	tmp;

	if (fdf->move.scale == 0)
		return (0);
	tmp = fdf->scale + fdf->move.scale;
	if (tmp <= 0)
		return (0);
	fdf->scale = tmp;
	return (1);
}

int	handle_depth(t_fdf *fdf)
{
	if (fdf->move.depth == 0)
		return (0);
	fdf->depth += fdf->move.depth;
	return (1);
}

int	handle_angle(t_fdf *fdf)
{
	double	rad;

	if (fdf->move.angle == 0)
		return (0);
	fdf->angle += fdf->move.angle;
	fdf->angle %= 360;
	rad = fdf->angle * M_PI / 180.0;
	fdf->angle_sin = sin(rad);
	fdf->angle_cos = cos(rad);
	return (1);
}

int	handle_proj(t_fdf *fdf, int keycode)
{
	if (keycode == 34)
	{
		fdf->proj = ISO;
		fdf->f_proj = &iso;
	}
	else if (keycode == 35)
	{
		fdf->proj = PARALLEL;
		fdf->f_proj = &parallel;
	}
	return (1);
}
