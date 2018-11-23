/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:58:04 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/23 20:39:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

static void		fill_out(t_opt *opt, t_out *out, t_flist *lst)
{
	t_flist	*current;

	out->f_count = 0;
	out->f_width = 0;
	current = lst;
	while (current != NULL)
	{
		(out->f_count)++;
		out->f_width = ft_max(out->f_width, ft_strlen(current->data->d_name));
		current = current->next;
	}
	(out->f_width)++;
	out->cols = ft_max(1, opt->ws.ws_col / out->f_width);
	out->rows = (out->f_count / out->cols) + (out->f_count % out->cols > 0);
	while ((out->cols * out->rows) - out->f_count >= out->rows)
	{
		out->cols--;
		out->rows = (out->f_count / out->cols) + (out->f_count % out->cols > 0);
	}
	out->size = out->cols * out->rows;
}

static t_flist	**prepare_columns(t_out *out, t_flist *lst)
{
	t_flist	**columns;
	t_flist	*current;
	int		col_index;
	int		index;

	if (!(columns = (t_flist **)malloc(out->cols * sizeof(*columns))))
		malloc_error();
	columns[0] = lst;
	current = lst;
	col_index = 1;
	while (col_index < out->cols)
	{
		index = 0;
		while (index < out->rows)
		{
			current = current->next;
			index++;
		}
		columns[col_index] = current;
		col_index++;
	}
	return (columns);
}

void			show_columns(t_opt *opt, t_flist *lst)
{
	t_out	out;
	t_flist	**columns;
	t_flist	*current;
	int		index;
	int		col_index;

	fill_out(opt, &out, lst);
	columns = prepare_columns(&out, lst);
	index = 0;
	while (index < out.size)
	{
		col_index = index % out.cols;
		if ((current = columns[col_index]) != NULL)
		{
			if ((col_index + 1) == out.cols || columns[col_index + 1] == NULL)
				ft_printf("%s\n", current->data->d_name);
			else
				ft_printf("%-*s", out.f_width, current->data->d_name);
			columns[col_index] = current->next;
		}
		index++;
	}
}
