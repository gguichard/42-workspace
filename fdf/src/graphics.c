/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:03:30 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/31 02:09:11 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static void	apply_off(t_fdf *fdf, t_pos *pos)
{
	pos->proj_x += (fdf->width / 2) - fdf->offset_x;
	pos->proj_y += (fdf->height / 2) - fdf->offset_y;
}

static void	draw_edge(t_fdf *fdf, t_pos *pos, t_pos offset)
{
	t_pos	*edge;

	edge = (fdf->pos)[(pos->y + offset.y) * fdf->cols + pos->x + offset.x];
	fdf->f_proj(fdf, edge);
	apply_off(fdf, edge);
	draw_line(fdf, *pos, *edge);
}

static void	draw_edges(t_fdf *fdf, t_pos *pos)
{
	t_pos	offset;

	fdf->f_proj(fdf, pos);
	apply_off(fdf, pos);
	if (pos->x + 1 < fdf->cols)
	{
		offset.x = 1;
		offset.y = 0;
		draw_edge(fdf, pos, offset);
	}
	if (pos->y + 1 < fdf->rows)
	{
		offset.x = 0;
		offset.y = 1;
		draw_edge(fdf, pos, offset);
	}
}

static void	compute_offsets(t_fdf *fdf)
{
	t_pos	*min;
	t_pos	*max;

	min = (fdf->pos)[0];
	max = (fdf->pos)[fdf->rows * fdf->cols - 1];
	fdf->f_proj(fdf, min);
	fdf->f_proj(fdf, max);
	fdf->offset_x = (max->proj_x - min->proj_x) * .5;
	fdf->offset_y = (max->proj_y - min->proj_y) * .5;
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
		draw_edges(fdf, fdf->pos[index]);
		index++;
	}
}
