/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:33:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/12 17:37:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "libft.h"
#include "fdf.h"
#include "vectors.h"
#include "error.h"
#include "wf_obj_parser.h"

static void		expand_bbox(t_vec3d *min, t_vec3d *max, t_vec3d *vertex)
{
	min->x = fmin(min->x, vertex->x);
	min->y = fmin(min->y, vertex->y);
	min->z = fmin(min->z, vertex->z);
	max->x = fmax(max->x, vertex->x);
	max->y = fmax(max->y, vertex->y);
	max->z = fmax(max->z, vertex->z);
}

static t_error	add_vertices_as_points(t_fdf *fdf, t_wf_obj *obj, t_vec3d *min
	, t_vec3d *max)
{
	size_t	idx;
	t_vec3d	*vertex;

	idx = 0;
	while (idx < obj->vertices.size)
	{
		vertex = ft_memalloc(sizeof(t_pos));
		if (vertex == NULL)
			return (ERR_UNEXPECTED);
		vertex->x = ((t_vec3d *)obj->vertices.data[idx])->x;
		vertex->y = ((t_vec3d *)obj->vertices.data[idx])->y;
		vertex->z = ((t_vec3d *)obj->vertices.data[idx])->z;
		if (!ft_vecpush(&fdf->pos, vertex))
		{
			free(vertex);
			return (ERR_UNEXPECTED);
		}
		expand_bbox(min, max, vertex);
		idx++;
	}
	return (ERR_NOERROR);
}

static void		translate_vertices(t_fdf *fdf, t_vec3d min, t_vec3d max)
{
	size_t	idx;
	t_vec3d	center;
	t_vec3d	*vertex;

	center = vec3d_add(min, vec3d_scalar(vec3d_sub(max, min), .5));
	idx = 0;
	while (idx < fdf->pos.size)
	{
		vertex = (t_vec3d *)fdf->pos.data[idx];
		*vertex = vec3d_sub(*vertex, center);
		idx++;
	}
}

t_error			read_obj_file(t_fdf *fdf)
{
	t_wf_obj	obj;
	t_error		err;
	t_vec3d		min;
	t_vec3d		max;

	err = parse_wf_obj_file((fdf->argv)[0], &obj, 5);
	if (err == ERR_NOERROR)
	{
		min = vec3d(INFINITY, INFINITY, INFINITY);
		max = vec3d(-INFINITY, -INFINITY, -INFINITY);
		err = add_vertices_as_points(fdf, &obj, &min, &max);
		if (err != ERR_NOERROR)
			ft_vecfree(&fdf->pos);
		else
			translate_vertices(fdf, min, max);
		free_wf_obj(&obj);
	}
	return (err);
}
