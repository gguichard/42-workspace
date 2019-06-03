/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 22:27:39 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/03 23:27:26 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "libft.h"
#include "select.h"

static t_item	**get_item_cols(t_select_format fmt, t_item *begin_lst)
{
	t_item	**cols;
	size_t	col;
	size_t	idx;
	t_item	*lst;

	cols = (t_item **)malloc(sizeof(t_item *) * fmt.max_col);
	if (cols != NULL)
	{
		col = 0;
		idx = 0;
		lst = begin_lst;
		while (lst != NULL && col < fmt.max_col)
		{
			while (idx++ != col * (fmt.max_row + 1))
				lst = lst->next;
			cols[col] = lst;
			col++;
		}
	}
	return (cols);
}

static void		print_single_item(t_select_format fmt, t_item *item)
{
	const char	*color;
	int			diff;

	color = "";
	if (S_ISDIR(item->file_mode))
		color = "\033[01;34m";
	else if (S_ISLNK(item->file_mode))
		color = "\033[01;36m";
	else if (S_ISSOCK(item->file_mode) || S_ISFIFO(item->file_mode))
		color = "\033[01;35m";
	else if (S_ISBLK(item->file_mode) || S_ISCHR(item->file_mode))
		color = "\033[40;33;01m";
	diff = fmt.col_width - ft_strlen(item->content);
	ft_printf("[%s%*s%s%*s\033[m]", color, diff / 2 + diff % 2 - 1, ""
		, item->content, diff / 2 - 1, "");
}

static void		print_items(t_select *select)
{
	t_select_format	fmt;
	t_item			*current;
	t_item			**cols;
	size_t			row;
	size_t			col;

	fmt = get_columns_format(select);
	current = select->cur_items;
	if (fmt.max_col == 0 || fmt.max_row == 0
		|| (cols = get_item_cols(fmt, current)) == NULL)
		return ;
	row = 0;
	while (row < fmt.max_row)
	{
		col = 0;
		while (col < fmt.max_col && cols[col] != NULL)
		{
			print_single_item(fmt, cols[col]);
			cols[col] = cols[col]->next;
			col++;
		}
		write(STDOUT_FILENO, "\n", 1);
		row++;
	}
	free(cols);
}

void			select_loop(t_select *select)
{
	ssize_t	read_size;
	char	buf;

	while (1)
	{
		print_items(select);
		read_size = read(STDIN_FILENO, &buf, 1);
		if (read_size <= 0)
		{
			ft_dprintf(STDERR_FILENO, "ft_select: unable to read from stdin\n");
			break ;
		}
		if (buf == '\033' || buf == '\n')
			break ;
	}
}
