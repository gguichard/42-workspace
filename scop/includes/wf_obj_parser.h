/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wf_obj_parser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 09:16:59 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/09 18:50:39 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WF_OBJ_PARSER_H
# define WF_OBJ_PARSER_H

# include "libft.h"
# include "error.h"

typedef struct		s_wf_obj
{
	t_vector		vertices;
	t_vector		tmp_vertices;
}					t_wf_obj;

void				free_wf_obj(t_wf_obj *obj);

void				wf_add_vertex_to_vector(t_vector *vector, char **split
	, double scale, t_error *err);
t_error				parse_wf_obj_file(const char *file, t_wf_obj *obj
	, double scale);

#endif
