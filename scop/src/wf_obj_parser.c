/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wf_obj_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 09:10:11 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/09 18:52:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "wf_obj_parser.h"
#include "error.h"

static void		parse_wf_f_line(t_wf_obj *obj, const char *part
	, t_error *err)
{
	char	*endptr;
	size_t	v_indice;

	*err = ERR_NOERROR;
	v_indice = ft_strtol(part, &endptr, 10);
	if (v_indice < 1 || v_indice > obj->tmp_vertices.size)
		*err = ERR_BADOBJFILE;
	else if (!ft_vecpush(&obj->vertices, obj->tmp_vertices.data[v_indice - 1]))
		*err = ERR_UNEXPECTED;
}

static void		push_wf_obj_indices(t_wf_obj *obj, char **split, t_error *err)
{
	size_t	idx;

	if (ft_strtab_count(split) < 4)
		*err = ERR_BADOBJFILE;
	else
	{
		*err = ERR_NOERROR;
		idx = 0;
		while (*err == ERR_NOERROR && idx < 3)
		{
			parse_wf_f_line(obj, split[idx + 1], err);
			idx++;
		}
	}
}

static t_error	parse_wf_obj_line(t_wf_obj *obj, const char *line, double scale)
{
	t_error	err;
	char	**split;

	err = ERR_NOERROR;
	split = ft_strsplit(line, ' ');
	if (split == NULL)
		return (ERR_UNEXPECTED);
	else if (ft_strequ(split[0], "f"))
		push_wf_obj_indices(obj, split, &err);
	else if (ft_strequ(split[0], "v"))
		wf_add_vertex_to_vector(&obj->tmp_vertices, split, scale, &err);
	ft_strtab_free(split);
	return (err);
}

t_error			parse_wf_obj_file(const char *file, t_wf_obj *obj, double scale)
{
	int		fd;
	char	*line;
	int		ret;
	t_error	err;

	ft_memset(obj, 0, sizeof(t_wf_obj));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ERR_ERRNO);
	err = ERR_NOERROR;
	while (err == ERR_NOERROR && (ret = get_next_line(fd, &line)) == 1)
	{
		if (line[0] != '#')
			err = parse_wf_obj_line(obj, line, scale);
		free(line);
	}
	if (ret != 0 && err == ERR_NOERROR)
		err = ERR_ERRNO;
	if (err != ERR_NOERROR)
		free_wf_obj(obj);
	close(fd);
	return (err);
}
