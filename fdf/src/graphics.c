/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:03:30 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/30 02:31:11 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line(t_fdf *fdf, int x1, int y1, int x2, int y2)
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

static void	draw_edges(t_fdf *fdf, t_pos *pos)
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	scale;

	scale = fdf->width
	iso(pos, &x1, &y1);
	iso((fdf->pos)[pos->y * fdf->cols + pos->x + 1], &x2, &y2);
	draw_line(fdf, x1, y1, x2, y2);
	iso((fdf->pos)[(pos->y + 1) * fdf->cols + pos->x], &x2, &y2);
	draw_line(fdf, x2, y2, x1, y1);
}

void		draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->rows - 1)
	{
		x = 0;
		while (x < fdf->cols - 1)
		{
			draw_edges(fdf, fdf->pos[y * fdf->cols + x]);
			x++;
		}
		y++;
	}
}
