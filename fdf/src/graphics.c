/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:03:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/11 22:23:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "fdf.h"
#include "matrix44.h"

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

static t_vec3d	proj_vec3d(t_fdf *fdf, t_vec3d vec)
{
	double	result[4][4];

	mat44_mul(fdf->matrix, fdf->matrix_translate, result);
	vec = mat44_apply(result, vec);
	vec.x += fdf->winsize.width / 2.;
	vec.y += fdf->winsize.height / 2.;
	return (vec);
}

static void		clear_window(t_fdf *fdf)
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

void			fill_window_image(t_fdf *fdf)
{
	size_t	index;

	clear_window(fdf);
	index = 0;
	if (fdf->use_obj_render)
	{
		while ((index + 3) <= fdf->pos.size)
		{
			draw_triangle(fdf, index
				, proj_vec3d(fdf, *(t_vec3d *)(fdf->pos.data)[index])
				, proj_vec3d(fdf, *(t_vec3d *)(fdf->pos.data)[index + 1])
				, proj_vec3d(fdf, *(t_vec3d *)(fdf->pos.data)[index + 2]));
			index += 3;
		}
	}
	else
	{
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
}
