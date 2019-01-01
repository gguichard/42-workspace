/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 00:35:52 by gguichar          #+#    #+#             */
/*   Updated: 2019/01/01 22:20:48 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

void	iso(t_pos pos, double *x, double *y)
{
	*x = (pos.x - pos.y) * cos(0.523599);
	*y = -(pos.z) + (pos.x + pos.y) * sin(0.523599);
}

void	parallel(t_pos pos, double *x, double *y)
{
	*x = pos.x - pos.z * cos(0.785398);
	*y = pos.y - pos.z * sin(0.785398);
}
