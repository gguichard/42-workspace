/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:03:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/09 18:49:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "fdf.h"
#include "matrix44.h"
#include "bresenham.h"

static void	proj_pos(t_fdf *fdf, t_pos *pos)
{
	t_vec3d	vec;
	double	result[4][4];

	vec.x = pos->x - fdf->cols / 2.;
	vec.y = pos->y - fdf->rows / 2.;
	vec.z = pos->z;
	mat44_mul(fdf->matrix, fdf->matrix_translate, result);
	vec = mat44_apply(result, vec);
	pos->proj.x = vec.x + fdf->winsize.width / 2.;
	pos->proj.y = vec.y + fdf->winsize.height / 2.;
}

static void	rasterize(t_fdf *fdf, t_pos pos, t_pos edge)
{
	if ((pos.proj.x < 0 && edge.proj.x < 0)
		|| (pos.proj.y < 0 && edge.proj.y < 0)
		|| (pos.proj.x >= fdf->winsize.width
			&& edge.proj.x >= fdf->winsize.width)
		|| (pos.proj.y >= fdf->winsize.height
			&& edge.proj.y >= fdf->winsize.height))
		return ;
	draw_line(fdf, pos, edge);
}

static void	draw_edges(t_fdf *fdf, t_pos pos)
{
	if (pos.x + 1 < fdf->cols)
		rasterize(fdf, pos
			, *(t_pos *)(fdf->pos.data)[pos.y * fdf->cols + pos.x + 1]);
	if (pos.y + 1 < fdf->rows)
		rasterize(fdf, pos
			, *(t_pos *)(fdf->pos.data)[(pos.y + 1) * fdf->cols + pos.x]);
}

static void	draw_triangle(t_fdf *fdf, t_pos pos_1, t_pos pos_2, t_pos pos_3)
{
	rasterize(fdf, pos_1, pos_2);
	rasterize(fdf, pos_1, pos_3);
	rasterize(fdf, pos_3, pos_2);
}

static void	clear_window(t_fdf *fdf)
{
	int	index;
	int	total;

	index = 0;
	total = fdf->winsize.width * fdf->winsize.height;
	while (index < total)
	{
		(fdf->z_buffer)[index] = INT_MIN;
		index++;
	}
	ft_memset(fdf->lib.img_data, 0, fdf->lib.size_line * fdf->winsize.height);
}

void		fill_window_image(t_fdf *fdf)
{
	int			index;
	int			total;

	clear_window(fdf);
	total = fdf->pos.size;
	index = 0;
	while (index < total)
	{
		proj_pos(fdf, (t_pos *)(fdf->pos.data)[index]);
		index++;
	}
	index = 0;
	if (!fdf->use_obj_render)
	{
		while (index < total)
		{
			draw_edges(fdf, *(t_pos *)(fdf->pos.data)[index]);
			index++;
		}
	}
	else
	{
		while ((index + 3) < total)
		{
			draw_triangle(fdf, *(t_pos *)(fdf->pos.data)[index]
				, *(t_pos *)(fdf->pos.data)[index + 1]
				, *(t_pos *)(fdf->pos.data)[index + 2]);
			index += 3;
		}
	}
}
