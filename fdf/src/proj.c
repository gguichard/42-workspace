/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 00:35:52 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/31 02:07:25 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

void	iso(t_fdf *fdf, t_pos *pos)
{
	double	x;
	double	y;

	x = pos->x * cos(fdf->angle_rad) - pos->y * sin(fdf->angle_rad);
	y = pos->x * sin(fdf->angle_rad) + pos->y * cos(fdf->angle_rad);
	pos->proj_x = fdf->scale * x * cos(0.523599);
	pos->proj_y = fdf->scale * (pos->z * fdf->depth * -.1 + y * sin(0.523599));
}

void	parallel(t_fdf *fdf, t_pos *pos)
{
	double	x;
	double	y;

	x = pos->x - pos->z * fdf->depth * .1 * cos(fdf->angle_rad);
	y = pos->y - pos->z * fdf->depth * .1 * sin(fdf->angle_rad);
	pos->proj_x = fdf->scale * x;
	pos->proj_y = fdf->scale * y;
}
