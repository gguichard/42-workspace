/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:04:07 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/22 19:30:56 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#include "line_draw.h"
#include "keys.h"

static t_vec3d		get_slope(t_vec3d vert_1, t_vec3d vert_2)
{
	t_vec3d	vec;
	double	dy;

	vec.y = 1.;
	dy = (int)vert_1.y - (int)vert_2.y;
	if (fabs(dy) < 1e-6)
	{
		vec.x = 0;
		vec.z = 0;
	}
	else
	{
		vec.x = (vert_1.x - vert_2.x) / dy;
		vec.z = (vert_1.z - vert_2.z) / dy;
	}
	return (vec);
}

static void			rasterize_triangle(t_fdf *fdf, t_vec3d vertices[3])
{
	t_vec3d	slopes[2];
	t_vec3d	trackers[2];

	slopes[0] = get_slope(vertices[1], vertices[0]);
	slopes[1] = get_slope(vertices[2], vertices[0]);
	trackers[0] = vertices[0];
	trackers[1] = vertices[0];
	while ((int)trackers[1].y <= (int)vertices[2].y)
	{
		if ((int)trackers[0].y == (int)vertices[1].y)
		{
			trackers[0] = vertices[1];
			slopes[0] = get_slope(vertices[2], vertices[1]);
		}
		draw_vline(fdf, trackers, 0xFFFFFF);
		trackers[0] = vec3d_add(trackers[0], slopes[0]);
		trackers[1] = vec3d_add(trackers[1], slopes[1]);
	}
}

static void			sort_vertices(t_vec3d vertices[3])
{
	size_t	idx;
	t_vec3d	tmp;

	idx = 0;
	while ((idx + 1) < 3)
	{
		if (vertices[idx].y > vertices[idx + 1].y)
		{
			tmp = vertices[idx];
			vertices[idx] = vertices[idx + 1];
			vertices[idx + 1] = tmp;
			if (idx > 0)
			{
				idx -= 1;
				continue ;
			}
		}
		idx++;
	}
}

static t_pos		vec3d_as_pos(t_vec3d vertex)
{
	t_pos	pos;

	pos.proj.x = vertex.x;
	pos.proj.y = vertex.y;
	pos.z = vertex.z;
	pos.color = 0xFFFFFF;
	return (pos);
}

void				draw_triangle(t_fdf *fdf
	, t_vec3d vert_1, t_vec3d vert_2, t_vec3d vert_3)
{
	t_vec3d	vertices[3];

	if (!(fdf->keys & ENABLE_RASTERIZATION))
	{
		draw_line(fdf, vec3d_as_pos(vert_1), vec3d_as_pos(vert_2));
		draw_line(fdf, vec3d_as_pos(vert_1), vec3d_as_pos(vert_3));
		draw_line(fdf, vec3d_as_pos(vert_3), vec3d_as_pos(vert_2));
	}
	else
	{
		vertices[0] = vert_1;
		vertices[1] = vert_2;
		vertices[2] = vert_3;
		sort_vertices(vertices);
		rasterize_triangle(fdf, vertices);
	}
}
