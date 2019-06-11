/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:04:07 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/11 02:33:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fdf.h"
#include "bresenham.h"

void		draw_edges(t_fdf *fdf, t_pos pos)
{
	if (pos.x + 1 < fdf->cols)
		draw_line(fdf, pos
			, *(t_pos *)(fdf->pos.data)[pos.y * fdf->cols + pos.x + 1]);
	if (pos.y + 1 < fdf->rows)
		draw_line(fdf, pos
			, *(t_pos *)(fdf->pos.data)[(pos.y + 1) * fdf->cols + pos.x]);
}

static double	get_slope(double x_diff, double y_diff)
{
	if (fabs(y_diff) < 0.0001)
		return (0);
	else
		return (x_diff / y_diff);
}

static t_pos	vec2d_as_pos(t_vec2d vec, unsigned int color)
{
	t_pos			pos;

	ft_memset(&pos, 0, sizeof(t_pos));
	pos.proj = vec;
	pos.color = color;
	return (pos);
}

static void	rasterize_triangle(t_fdf *fdf, t_pos highest_pos, t_pos pos_a
	, t_pos pos_b)
{
	double			slope_a;
	double			slope_b;
	t_vec2d			tracker_a;
	t_vec2d			tracker_b;
	unsigned char	c;
	unsigned int	color;

	c = (rand() / (double)RAND_MAX) * 255;
	color = 0xFFFFFF;//(c << 16) | (c << 8) | c;
	slope_a = get_slope((int)pos_a.proj.x - (int)highest_pos.proj.x
		, (int)pos_a.proj.y - (int)highest_pos.proj.y);
	slope_b = get_slope((int)pos_b.proj.x - (int)highest_pos.proj.x
		, (int)pos_b.proj.y - (int)highest_pos.proj.y);
	tracker_a = highest_pos.proj;
	tracker_b = highest_pos.proj;
	while (1)
	{
		draw_line(fdf, vec2d_as_pos(tracker_a, color)
			, vec2d_as_pos(tracker_b, color));
		if ((int)tracker_b.y == (int)pos_b.proj.y)
			break ;
		else if ((int)tracker_a.y == (int)pos_a.proj.y)
		{
			tracker_a.x = pos_a.proj.x;
			slope_a = get_slope((int)pos_b.proj.x - (int)tracker_a.x
					, (int)pos_b.proj.y - (int)tracker_a.y);
		}
		tracker_a.x += slope_a;
		tracker_b.x += slope_b;
		tracker_a.y += 1.;
		tracker_b.y += 1.;
	}
}

void		draw_triangle(t_fdf *fdf, t_pos pos_1, t_pos pos_2, t_pos pos_3)
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
