/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:04:07 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/11 22:43:22 by gguichar         ###   ########.fr       */
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

static double	get_slope(t_vec3d vec_a, t_vec3d vec_b)
{
	double	x_diff;
	double	y_diff;

	x_diff = (int)vec_a.x - (int)vec_b.x;
	y_diff = (int)vec_a.y - (int)vec_b.y;
	if (fabs(y_diff) < 1e-4)
		return (0);
	else
		return (x_diff / y_diff);
}

static void		draw_vline(t_fdf *fdf, t_vec3d tracker_1, t_vec3d tracker_2
	, unsigned int color)
{
	int		y;
	int		x0;
	int		x1;
	int		x;
	double	z0;
	double	z1;
	int		index;
	int		z;
	double	percent;

	y = tracker_2.y;
	if (y < 0 || y >= fdf->winsize.height)
		return ;
	else if (tracker_1.x < tracker_2.x)
	{
		x0 = tracker_1.x;
		x1 = tracker_2.x;
		z0 = tracker_1.z;
		z1 = tracker_2.z;
	}
	else
	{
		x0 = tracker_2.x;
		x1 = tracker_1.x;
		z0 = tracker_2.z;
		z1 = tracker_1.z;
	}
	x = x0;
	while (x <= x1)
	{
		if (x >= 0 && x < fdf->winsize.width)
		{
			index = y * fdf->winsize.width + x;
			percent = pcnt(x0, x1, x);
			z = (int)((1 - percent) * z0 + percent * z1);
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
	double			invslope_1;
	double			invslope_2;
	double			zincr_1;
	double			zincr_2;
	t_vec3d			tracker_1;
	t_vec3d			tracker_2;
	unsigned int	color;
	double			percent;
	unsigned char	comp;

	invslope_1 = get_slope(vert_1, highest_vert);
	invslope_2 = get_slope(vert_2, highest_vert);
	zincr_1 = (vert_1.z - highest_vert.z) / (vert_1.y - highest_vert.y);
	zincr_2 = (vert_2.z - highest_vert.z) / (vert_2.y - highest_vert.y);
	tracker_1 = highest_vert;
	tracker_2 = highest_vert;
	percent = (index / (double)fdf->pos.size);
	comp = 255 * index;
	color = (comp << 16) | (comp << 8) | comp;
	while ((int)tracker_2.y <= (int)vert_2.y)
	{
		if ((int)tracker_1.y == (int)vert_1.y)
		{
			tracker_1 = vert_1;
			invslope_1 = get_slope(vert_2, vert_1);
			zincr_1 = (vert_2.z - vert_1.z) / (vert_2.y - vert_1.y);
		}
		draw_vline(fdf, tracker_1, tracker_2, color);
		tracker_1.x += invslope_1;
		tracker_2.x += invslope_2;
		tracker_1.y += 1.;
		tracker_2.y += 1.;
		tracker_1.z += zincr_1;
		tracker_2.z += zincr_2;
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
