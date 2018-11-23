/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:58:04 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/23 16:18:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

static void	fill_out(t_opt *opt, t_out *out, t_flist *lst)
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
	out->cols = ft_min(9, opt->ws.ws_col / out->f_width);
	out->lines = out->f_count / out->cols;
	if (out->f_count % out->cols != 0)
		out->lines++;
}

void		show_columns(t_opt *opt, t_flist *lst)
{
	t_out	out;
	t_flist	*current;
	t_flist	**columns;
	int		index;
	int		col_index;

	fill_out(opt, &out, lst);
	if (!(columns = (t_flist **)malloc(out.cols * sizeof(*columns))))
		malloc_error();
	current = lst;
	index = 0;
	col_index = 0;
	while (current != NULL)
	{
		if (index % out.lines == 0)
			columns[col_index++] = current;
		current = current->next;
		index++;
	}
	index = 0;
	while (index < out.f_count)
	{
		col_index = index % out.cols;
		current = columns[col_index];
		if ((index + 1) == out.f_count || (index + 1) % out.cols == 0)
			ft_printf("%s\n", current->data->d_name);
		else
			ft_printf("%-*s", out.f_width, current->data->d_name);
		columns[col_index] = current->next;
		index++;
	}
}
