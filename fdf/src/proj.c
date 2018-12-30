/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 00:35:52 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/30 21:27:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

void	iso(t_fdf *fdf, t_point *point, t_pos *to)
{
	double	x;
	double	y;

	x = point->x * cos(fdf->angle_rad) - point->y * sin(fdf->angle_rad);
	y = point->x * sin(fdf->angle_rad) + point->y * cos(fdf->angle_rad);
	to->x = fdf->scale * x * cos(0.523599);
	to->y = fdf->scale * (-(point->z * fdf->depth * .1) + y * sin(0.523599));
}

void	parallel(t_fdf *fdf, t_point *point, t_pos *to)
{
	double	x;
	double	y;

	x = point->x - point->z * fdf->depth * .1 * cos(fdf->angle_rad);
	y = point->y - point->z * fdf->depth * .1 * sin(fdf->angle_rad);
	to->x = fdf->scale * x;
	to->y = fdf->scale * y;
}
