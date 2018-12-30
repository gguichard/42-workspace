/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 00:35:52 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/30 07:45:56 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

void	iso(t_fdf *fdf, t_point *point, t_pos *to)
{
	to->x = fdf->scale * ((point->x - point->y) * cos(0.523599));
	to->y = fdf->scale * (-(point->z * fdf->depth * .1 )+ (point->x + point->y)
			* sin(0.523599));
}

void	parallel(t_fdf *fdf, t_point *point, t_pos *to)
{
	to->x = fdf->scale * (point->x - point->z * fdf->depth * .1
			* cos(0.785398));
	to->y = fdf->scale * (point->y - point->z * fdf->depth * .1
			* sin(0.785398));
}
