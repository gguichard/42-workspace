/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:33:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/10 18:02:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "fdf.h"
#include "error.h"
#include "wf_obj_parser.h"

static t_error	add_vertices_as_points(t_fdf *fdf, t_wf_obj *obj)
{
	size_t	idx;
	t_pos	*pos;

	idx = 0;
	while (idx < obj->vertices.size)
	{
		pos = ft_memalloc(sizeof(t_pos));
		if (pos == NULL)
			return (ERR_UNEXPECTED);
		pos->x = ((t_vec3d *)obj->vertices.data[idx])->x;
		pos->y = ((t_vec3d *)obj->vertices.data[idx])->y;
		pos->z = ((t_vec3d *)obj->vertices.data[idx])->z;
		pos->color = 0xFFFFFF;
		if (!ft_vecpush(&fdf->pos, pos))
		{
			free(pos);
			return (ERR_UNEXPECTED);
		}
		idx++;
	}
	return (ERR_NOERROR);
}

t_error			read_obj_file(t_fdf *fdf)
{
	t_wf_obj	obj;
	t_error		err;

	err = parse_wf_obj_file((fdf->argv)[0], &obj, 5);
	if (err == ERR_NOERROR)
	{
		err = add_vertices_as_points(fdf, &obj);
		if (err != ERR_NOERROR)
			ft_vecfree(&fdf->pos);
		free_wf_obj(&obj);
	}
	return (err);
}
