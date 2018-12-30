/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:03:30 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/30 06:40:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static void	apply_offsets(t_fdf *fdf, t_pos *pos)
{
	pos->x += (fdf->width / 2) - fdf->offset_x;
	pos->y += (fdf->height / 2) - fdf->offset_y;
}

static void	draw_edges(t_fdf *fdf, t_pos *pos)
{
	t_pos	pos1;
	t_pos	pos2;

	fdf->f_proj(fdf, pos, &pos1);
	apply_offsets(fdf, &pos1);
	if (pos->x + 1 < fdf->cols)
	{
		fdf->f_proj(fdf, (fdf->pos)[pos->y * fdf->cols + pos->x + 1], &pos2);
		apply_offsets(fdf, &pos2);
		draw_line(fdf, pos1, pos2);
	}
	if (pos->y + 1 < fdf->rows)
	{
		fdf->f_proj(fdf, (fdf->pos)[(pos->y + 1) * fdf->cols + pos->x], &pos2);
		apply_offsets(fdf, &pos2);
		draw_line(fdf, pos1, pos2);
	}
}

static void	compute_offsets(t_fdf *fdf)
{
	t_pos	pos;
	t_pos	min;
	t_pos	max;

	pos.x = 0;
	pos.y = 0;
	fdf->f_proj(fdf, &pos, &min);
	pos.x = fdf->cols;
	pos.y = fdf->rows;
	fdf->f_proj(fdf, &pos, &max);
	fdf->offset_x = (max.x - min.x) / 2;
	fdf->offset_y = (max.y - min.y) / 2;
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
