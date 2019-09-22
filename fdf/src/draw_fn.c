/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:16:43 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/22 17:09:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "matrix44.h"
#include "line_draw.h"

static void		proj_pos(t_fdf *fdf, t_pos *pos)
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

static void		draw_edges(t_fdf *fdf, t_pos pos)
{
	if (pos.x + 1 < fdf->cols)
		draw_line(fdf, pos
			, *(t_pos *)(fdf->pos.data)[pos.y * fdf->cols + pos.x + 1]);
	if (pos.y + 1 < fdf->rows)
		draw_line(fdf, pos
			, *(t_pos *)(fdf->pos.data)[(pos.y + 1) * fdf->cols + pos.x]);
}

static t_vec3d	proj_vec3d(t_fdf *fdf, t_vec3d vec)
{
	double	result[4][4];

	mat44_mul(fdf->matrix, fdf->matrix_translate, result);
	vec = mat44_apply(result, vec);
	vec.x += fdf->winsize.width / 2.;
	vec.y += fdf->winsize.height / 2.;
	return (vec);
}

void			draw_regular_points(t_fdf *fdf)
{
	size_t	index;

	index = 0;
	while (index < fdf->pos.size)
	{
		proj_pos(fdf, (t_pos *)(fdf->pos.data)[index]);
		index++;
	}
	index = 0;
	while (index < fdf->pos.size)
	{
		draw_edges(fdf, *(t_pos *)(fdf->pos.data)[index]);
		index++;
	}
}

void			draw_obj_vertices(t_fdf *fdf)
{
	size_t	index;

	index = 0;
	while ((index + 3) <= fdf->pos.size)
	{
		draw_triangle(fdf
			, proj_vec3d(fdf, *(t_vec3d *)(fdf->pos.data)[index])
			, proj_vec3d(fdf, *(t_vec3d *)(fdf->pos.data)[index + 1])
			, proj_vec3d(fdf, *(t_vec3d *)(fdf->pos.data)[index + 2]));
		index += 3;
	}
}
