/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:03:30 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/30 07:49:17 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static void	apply_off(t_fdf *fdf, t_pos *pos)
{
	pos->x += (fdf->width / 2) - fdf->offset_x;
	pos->y += (fdf->height / 2) - fdf->offset_y;
}

static void	draw_edges(t_fdf *fdf, t_point *point)
{
	t_pos	pos1;
	t_pos	pos2;

	fdf->f_proj(fdf, point, &pos1);
	apply_off(fdf, &pos1);
	if (point->x + 1 < fdf->cols)
	{
		point->x += 1;
		fdf->f_proj(fdf, (fdf->point)[point_to_index(fdf, point)], &pos2);
		apply_off(fdf, &pos2);
		draw_line(fdf, pos1, pos2);
		point->x -= 1;
	}
	if (point->y + 1 < fdf->rows)
	{
		point->y += 1;
		fdf->f_proj(fdf, (fdf->point)[point_to_index(fdf, point)], &pos2);
		apply_off(fdf, &pos2);
		draw_line(fdf, pos1, pos2);
		point->y -= 1;
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
