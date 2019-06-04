/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 22:27:39 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/04 16:23:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "libft.h"
#include "select.h"
#include "items.h"
#include "hotkeys.h"

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

static void		print_single_item(int fd, t_select_format fmt, t_item *item
	, int is_cursor)
{
	const char	*color;
	int			diff;

	write(fd, "[", 1);
	if (item->flags & SELECTED_FLAG)
		tputs(tgetstr("mr", NULL), 1, t_putchar);
	if (is_cursor)
		tputs(tgetstr("us", NULL), 1, t_putchar);
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
	ft_dprintf(fd, "%s%*s%s%*s\033[m", color, diff / 2 + diff % 2 - 1, ""
		, item->content, diff / 2 - 1, "");
	if (is_cursor)
		tputs(tgetstr("ue", NULL), 1, t_putchar);
	if (item->flags & SELECTED_FLAG)
		tputs(tgetstr("me", NULL), 1, t_putchar);
	write(fd, "]", 1);
}

void			print_items(t_select *select)
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
	tputs(tgetstr("cl", NULL), 1, t_putchar);
	row = 0;
	while (row < fmt.max_row)
	{
		col = 0;
		while (col < fmt.max_col && cols[col] != NULL)
		{
			print_single_item(select->tty_fd, fmt, cols[col]
				, (select->cursor_item == cols[col]));
			cols[col] = cols[col]->next;
			col++;
		}
		write(select->tty_fd, "\n", 1);
		row++;
	}
	free(cols);
}

void			select_loop(t_select *select)
{
	ssize_t	size_read;
	char	buf[8];
	int		hotkey;

	while (select->cur_items != NULL)
	{
		print_items(select);
		size_read = read(STDIN_FILENO, buf, sizeof(buf));
		if (size_read < 0)
		{
			ft_dprintf(STDERR_FILENO, "ft_select: unable to read from stdin\n");
			break ;
		}
		ft_memcpy(select->hotkeys_buf, buf, size_read);
		select->hotkeys_buf[size_read] = '\0';
		hotkey = hotkey_match(select->hotkeys, select->hotkeys_buf);
		if (hotkey == HOTKEY_ESC || hotkey == HOTKEY_ENTER)
			break ;
	}
}
