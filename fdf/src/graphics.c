/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:03:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/01/01 01:50:10 by gguichar         ###   ########.fr       */
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
	if ((pos->proj_x < 0 && edge->proj_x < 0)
			|| (pos->proj_y < 0 && edge->proj_y < 0)
			|| (pos->proj_x >= fdf->width && edge->proj_x >= fdf->width)
			|| (pos->proj_y >= fdf->height && edge->proj_y >= fdf->height))
		return ;
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
	t_pos	delta;
	int		size;

	min = (fdf->pos)[0];
	max = (fdf->pos)[fdf->rows * fdf->cols - 1];
	fdf->f_proj(fdf, min);
	fdf->f_proj(fdf, max);
	delta.x = (max->proj_x - min->proj_x); 
	delta.y = (max->proj_y - min->proj_y);
	size = ft_max(ft_abs(delta.x), ft_abs(delta.y));
	fdf->offset_x = delta.x * .5 - (fdf->cam.x * size * .01);
	fdf->offset_y = delta.y * .5 - (fdf->cam.y * size * .01);
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
