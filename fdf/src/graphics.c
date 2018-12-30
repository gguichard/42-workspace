/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:03:30 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/30 08:21:45 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static void	apply_off(t_fdf *fdf, t_pos *pos)
{
	pos->x += (fdf->width / 2) - fdf->offset_x;
	pos->y += (fdf->height / 2) - fdf->offset_y;
}

static void	draw_edge(t_fdf *fdf, t_pos pos, t_point *point, t_pos offset)
{
	t_point	*edge;
	t_pos	edge_pos;
	int		color;

	edge = (fdf->point)
		[(point->y + offset.y) * fdf->cols + point->x + offset.x];
	fdf->f_proj(fdf, edge, &edge_pos);
	apply_off(fdf, &edge_pos);
	color = ft_abs(point->z) > ft_abs(edge->z) ? point->color : edge->color;
	draw_line(fdf, pos, edge_pos, color);
}

static void	draw_edges(t_fdf *fdf, t_point *point)
{
	t_pos	pos;
	t_pos	offset;

	fdf->f_proj(fdf, point, &pos);
	apply_off(fdf, &pos);
	if (point->x + 1 < fdf->cols)
	{
		offset.x = 1;
		offset.y = 0;
		draw_edge(fdf, pos, point, offset);
	}
	if (point->y + 1 < fdf->rows)
	{
		offset.x = 0;
		offset.y = 1;
		draw_edge(fdf, pos, point, offset);
	}
}

static void	compute_offsets(t_fdf *fdf)
{
	t_pos	min;
	t_pos	max;

	fdf->f_proj(fdf, fdf->point[0], &min);
	fdf->f_proj(fdf, fdf->point[fdf->rows * fdf->cols - 1], &max);
	fdf->offset_x = (max.x - min.x) * .5;
	fdf->offset_y = (max.y - min.y) * .5;
}

void		fill_window_image(t_fdf *fdf)
{
	int	index;
	int	total;

	compute_offsets(fdf);
	ft_memset(fdf->lib.img_data, 0, fdf->lib.size_line * fdf->height);
	index = 0;
	total = fdf->rows * fdf->cols;
	while (index < total)
	{
		draw_edges(fdf, fdf->point[index]);
		index++;
	}
}
