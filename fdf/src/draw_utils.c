/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:04:07 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/11 23:39:31 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fdf.h"
#include "bresenham.h"

void			draw_edges(t_fdf *fdf, t_pos pos)
{
	if (pos.x + 1 < fdf->cols)
		draw_line(fdf, pos
			, *(t_pos *)(fdf->pos.data)[pos.y * fdf->cols + pos.x + 1]);
	if (pos.y + 1 < fdf->rows)
		draw_line(fdf, pos
			, *(t_pos *)(fdf->pos.data)[(pos.y + 1) * fdf->cols + pos.x]);
}

static t_vec3d	get_slope(t_vec3d vert_1, t_vec3d vert_2)
{
	t_vec3d	vec;
	double	y_diff;

	y_diff = (int)vert_1.y - (int)vert_2.y;
	if (fabs(y_diff) < 1e-6)
	{
		vec.x = 0;
		vec.z = 0;
	}
	else
	{
		vec.x = (vert_1.x - vert_2.x) / y_diff;
		vec.z = (vert_1.z - vert_2.z) / y_diff;
	}
	vec.y = 1.;
	return (vec);
}

static void		draw_vline(t_fdf *fdf, t_vec3d tracker_1, t_vec3d tracker_2
	, unsigned int color)
{
	int		x0;
	int		x1;
	double	z0;
	double	z1;
	int		x;
	int		y;
	int		z;
	int		index;
	double	percent;

	y = tracker_2.y;
	if (y < 0 || y >= fdf->winsize.height)
		return ;
	x0 = fmin(tracker_1.x, tracker_2.x);
	x1 = fmax(tracker_1.x, tracker_2.x);
	z0 = (x0 == (int)tracker_1.x ? tracker_1.z : tracker_2.z);
	z1 = (x0 == (int)tracker_1.x ? tracker_2.z : tracker_1.z);
	x = x0;
	while (x <= x1)
	{
		if (x >= 0 && x < fdf->winsize.width)
		{
			index = y * fdf->winsize.width + x;
			percent = pcnt(x0, x1, x);
			z = (1 - percent) * z0 + percent * z1;
			if ((fdf->z_buffer)[index] < z)
			{
				(fdf->z_buffer)[index] = z;
				fdf->lib.img_data[index] = color;
			}
		}
		x++;
	}
}

static void		rasterize_triangle(t_fdf *fdf, int index, t_vec3d highest_vert
	, t_vec3d vert_1, t_vec3d vert_2)
{
	t_vec3d			slope_1;
	t_vec3d			slope_2;
	t_vec3d			tracker_1;
	t_vec3d			tracker_2;
	unsigned char	part;
	unsigned int	color;

	slope_1 = get_slope(vert_1, highest_vert);
	slope_2 = get_slope(vert_2, highest_vert);
	tracker_1 = highest_vert;
	tracker_2 = highest_vert;
	part = 255 * (index / (double)fdf->pos.size);
	color = (part << 16) | (part << 8) | part;
	while ((int)tracker_2.y <= (int)vert_2.y)
	{
		if ((int)tracker_1.y == (int)vert_1.y)
		{
			tracker_1 = vert_1;
			slope_1 = get_slope(vert_2, vert_1);
		}
		draw_vline(fdf, tracker_1, tracker_2, color);
		tracker_1 = vec3d_add(tracker_1, slope_1);
		tracker_2 = vec3d_add(tracker_2, slope_2);
	}
}

void			draw_triangle(t_fdf *fdf, int index, t_vec3d vec_1
	, t_vec3d vec_2, t_vec3d vec_3)
{
	t_vec3d	vectors[3];
	t_vec3d	tmp;
	size_t	idx;

	vectors[0] = vec_1;
	vectors[1] = vec_2;
	vectors[2] = vec_3;
	idx = 0;
	while ((idx + 1) < (sizeof(vectors) / sizeof(vectors[0])))
	{
		if (vectors[idx].y > vectors[idx + 1].y)
		{
			tmp = vectors[idx];
			vectors[idx] = vectors[idx + 1];
			vectors[idx + 1] = tmp;
			if (idx > 0)
			{
				idx -= 1;
				continue ;
			}
		}
		idx++;
	}
	rasterize_triangle(fdf, index, vectors[0], vectors[1], vectors[2]);
}
