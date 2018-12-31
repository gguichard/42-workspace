/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 00:35:52 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/31 06:55:56 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

void	iso(t_fdf *fdf, t_pos *pos)
{
	double	x;
	double	y;

	x = pos->x * fdf->angle_cos - pos->y * fdf->angle_sin;
	y = pos->x * fdf->angle_sin + pos->y * fdf->angle_cos;
	pos->proj_x = fdf->scale * x * cos(0.523599);
	pos->proj_y = fdf->scale * (pos->z * fdf->depth * -.1 + y * sin(0.523599));
}

void	parallel(t_fdf *fdf, t_pos *pos)
{
	double	x;
	double	y;

	x = pos->x - pos->z * fdf->depth * .1 * fdf->angle_cos;
	y = pos->y - pos->z * fdf->depth * .1 * fdf->angle_sin;
	pos->proj_x = fdf->scale * x;
	pos->proj_y = fdf->scale * y;
}
