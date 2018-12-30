/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 00:35:52 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/30 06:53:58 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

void	iso(t_fdf *fdf, t_pos *pos, t_pos *to)
{
	to->x = (pos->x - pos->y) * cos(0.523599) * fdf->scale;
	to->y = -(pos->z * fdf->depth) + (pos->x + pos->y)
		* sin(0.523599) * fdf->scale;
}

void	parallel(t_fdf *fdf, t_pos *pos, t_pos *to)
{
	to->x = fdf->scale * (pos->x - pos->z * fdf->depth / 10 * cos(0.785398));
	to->y = fdf->scale * (pos->y - pos->z * fdf->depth / 10 * sin(0.785398));
}
