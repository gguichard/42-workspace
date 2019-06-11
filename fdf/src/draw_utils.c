/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:04:07 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/11 16:47:17 by gguichar         ###   ########.fr       */
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

static double	get_slope(t_pos pos_a, t_pos pos_b)
{
	double	x_diff;
	double	y_diff;

	x_diff = (int)pos_a.proj.x - (int)pos_b.proj.x;
	y_diff = (int)pos_a.proj.y - (int)pos_b.proj.y;
	if (fabs(y_diff) < 1e-4)
		return (0);
	else
		return (x_diff / y_diff);
}

static void		draw_vline(t_fdf *fdf, int x0, int x1, int y)
{
	int	tmp;

	if (y < 0 || y >= fdf->winsize.height)
		return ;
	else if (x1 < x0)
	{
		tmp = x0;
		x0 = x1;
		x1 = tmp;
	}
	while (x0 <= x1)
	{
		if (x0 >= 0 && x0 < fdf->winsize.width)
			fdf->lib.img_data[y * fdf->winsize.width + x0] = 0xFFFFFF;
		x0++;
	}
}

static void		rasterize_triangle(t_fdf *fdf, t_pos highest_pos, t_pos pos_a
	, t_pos pos_b)
{
	double	invslope_a;
	double	invslope_b;
	t_pos	tracker_a;
	t_pos	tracker_b;

	invslope_a = get_slope(pos_a, highest_pos);
	invslope_b = get_slope(pos_b, highest_pos);
	tracker_a = highest_pos;
	tracker_b = highest_pos;
	while ((int)tracker_b.proj.y <= (int)pos_b.proj.y)
	{
		if ((int)tracker_a.proj.y == (int)pos_a.proj.y)
		{
			tracker_a.proj = pos_a.proj;
			invslope_a = get_slope(pos_b, pos_a);
		}
		draw_vline(fdf, tracker_a.proj.x, tracker_b.proj.x, tracker_b.proj.y);
		tracker_a.proj.x += invslope_a;
		tracker_b.proj.x += invslope_b;
		tracker_a.proj.y += 1.;
		tracker_b.proj.y += 1.;
	}
}

void			draw_triangle(t_fdf *fdf, t_pos pos_1, t_pos pos_2, t_pos pos_3)
{
	t_pos	pos[3];
	t_pos	tmp;
	size_t	idx;

	pos[0] = pos_1;
	pos[1] = pos_2;
	pos[2] = pos_3;
	idx = 0;
	while ((idx + 1) < (sizeof(pos) / sizeof(pos[0])))
	{
		if (pos[idx].proj.y > pos[idx + 1].proj.y)
		{
			tmp = pos[idx];
			pos[idx] = pos[idx + 1];
			pos[idx + 1] = tmp;
			if (idx > 0)
			{
				idx -= 1;
				continue ;
			}
		}
		idx++;
	}
	rasterize_triangle(fdf, pos[0], pos[1], pos[2]);
}
