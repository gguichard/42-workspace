/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:03:30 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/29 18:14:09 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_fdf *fdf, int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;
	int	delta;

	dx = x2 - x1;
	dy = y2 - y1;
	delta = 2 * dy - dx;
	while (x1 <= x2)
	{
		fdf->lib.img_data[y1 * fdf->width + x1] = 0xFFFFFF;
		if (delta > 0)
		{
			y1 += 1;
			delta -= 2 * dx;
		}
		delta += 2 * dy;
		x1++;
	}
}

void	draw_map(t_fdf *fdf)
{
	(void)fdf;
}
