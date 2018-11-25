/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:58:04 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/25 20:16:54 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

static void		fill_out(t_opt *opt, t_out *out, t_flist *lst)
{
	int		count;
	t_flist	*current;

	count = 0;
	out->w_file = 0;
	current = lst;
	while (current != NULL)
	{
		count++;
		out->w_file = ft_max(out->w_file, ft_strlen(current->name));
		current = current->next;
	}
	(out->w_file)++;
	out->cols = ft_max(1, opt->ws.ws_col / out->w_file);
	out->rows = (count / out->cols) + (count % out->cols > 0);
	while ((out->cols * out->rows) - count >= out->rows)
	{
		out->cols--;
		out->rows = (count / out->cols) + (count % out->cols > 0);
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
		return (NULL);
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
				ft_printf("%s\n", current->name);
			else
				ft_printf("%-*s", out.w_file, current->name);
			columns[col_index] = current->next;
		}
		index++;
	}
}

static void		fill_out_padding(t_out *out, t_flist *lst)
{
	out->w_links = 0;
	out->w_user = 0;
	out->w_group = 0;
	out->w_size = 0;
	while (lst != NULL)
	{
		out->w_links = ft_max(ft_llsize(lst->stat.st_nlink), out->w_links);
		out->w_user = ft_max(ft_strlen(lst->pw_name), out->w_user);
		out->w_group = ft_max(ft_strlen(lst->gr_name), out->w_group);
		out->w_size = ft_max(ft_llsize(lst->stat.st_size), out->w_size);
		lst = lst->next;
	}
}

static void		show_simple_extended(t_flist *lst)
{
	t_out	out;
	mode_t	mode;

	fill_out_padding(&out, lst);
	while (lst != NULL)
	{
		mode = lst->stat.st_mode;
		ft_printf("%c%c%c%c%c%c%c%c%c%c%c %*d %-*s  %-*s  %*d %s %s\n"
				, f_type(mode)
				, f_perm(mode >> 6, 4), f_perm(mode >> 6, 2), f_perm(mode >> 6, 1)
				, f_perm(mode >> 3, 4), f_perm(mode >> 3, 2), f_perm(mode >> 3, 1)
				, f_perm(mode, 4), f_perm(mode, 2), f_perm(mode, 1)
				, ' '
				, out.w_links, lst->stat.st_nlink
				, out.w_user, lst->pw_name
				, out.w_group, lst->gr_name
				, out.w_size, lst->stat.st_size
				, "24 nov 15:42"
				, lst->name);
		lst = lst->next;
	}
}

void			show_simple(t_opt *opt, t_flist *lst)
{
	if (opt->options & LST_OPT)
	{
		show_simple_extended(lst);
		return ;
	}
	while (lst != NULL)
	{
		ft_printf("%s\n", lst->name);
		lst = lst->next;
	}
}
