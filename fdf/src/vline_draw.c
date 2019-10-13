/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vline_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 19:26:57 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/22 19:27:29 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#include "line_draw.h"

static inline void	plot_pixel(t_fdf *fdf, int index, int z, unsigned int color)
{
	if ((fdf->z_buffer)[index] < z)
	{
		(fdf->z_buffer)[index] = z;
		fdf->lib.img_data[index] = color;
	}
}

void				draw_vline(t_fdf *fdf, t_vec3d pos[2], unsigned int color)
{
	t_vline	vline;
	size_t	index;

	vline.y = pos[1].y;
	if (vline.y < 0 || vline.y >= fdf->winsize.height)
		return ;
	vline.x0 = fmin(pos[0].x, pos[1].x);
	vline.x1 = fmax(pos[0].x, pos[1].x);
	vline.z0 = (vline.x0 == (int)pos[0].x ? pos[0].z : pos[1].z);
	vline.z1 = (vline.x0 == (int)pos[0].x ? pos[1].z : pos[0].z);
	vline.x = vline.x0;
	while (vline.x <= vline.x1)
	{
		if (vline.x >= 0 && vline.x < fdf->winsize.width)
		{
			vline.z = (int)flint(vline.z0, vline.z1
					, pcnt(vline.x0, vline.x1, vline.x));
			index = vline.y * fdf->winsize.width + vline.x;
			plot_pixel(fdf, index, vline.z, color);
		}
		vline.x++;
	}
}
