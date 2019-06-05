/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 22:27:39 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/05 13:24:48 by gguichar         ###   ########.fr       */
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

static char	*get_item_color(t_item *item)
{
	char	*color;

	color = "";
	if (S_ISDIR(item->file_mode))
		color = "\033[01;34m";
	else if (S_ISLNK(item->file_mode))
		color = "\033[01;36m";
	else if (S_ISSOCK(item->file_mode) || S_ISFIFO(item->file_mode))
		color = "\033[01;35m";
	else if (S_ISBLK(item->file_mode) || S_ISCHR(item->file_mode))
		color = "\033[40;33;01m";
	return (color);
}

void		print_single_item(t_select *select, t_item *item)
{
	static char	*cm_tcap = NULL;
	int			diff;

	if (cm_tcap == NULL)
		cm_tcap = tgetstr("cm", NULL);
	tputs(tgoto(cm_tcap, item->col * select->format.col_width, item->row), 1
		, t_putchar);
	write(select->tty_fd, "[", 1);
	if (item->flags & SELECTED_FLAG)
		tputs(tgetstr("mr", NULL), 1, t_putchar);
	if (select->cursor_item == item)
		tputs(tgetstr("us", NULL), 1, t_putchar);
	diff = select->format.col_width - ft_strlen(item->content);
	ft_dprintf(select->tty_fd, "%s%*s%s%*s\033[m", get_item_color(item)
		, diff / 2 + diff % 2 - 1, "", item->content, diff / 2 - 1, "");
	if (select->cursor_item == item)
		tputs(tgetstr("ue", NULL), 1, t_putchar);
	if (item->flags & SELECTED_FLAG)
		tputs(tgetstr("me", NULL), 1, t_putchar);
	write(select->tty_fd, "]", 1);
}

void		print_select_items(t_select *select)
{
	static char	*cl_tcap = NULL;
	size_t		cols;
	size_t		idx;
	t_item		*current;

	if (cl_tcap == NULL)
		cl_tcap = tgetstr("cl", NULL);
	tputs(cl_tcap, 1, t_putchar);
	cols = ft_max(select->winsize.ws_col / select->format.col_width, 1);
	idx = 0;
	current = select->cur_items;
	while (current != NULL)
	{
		current->row = idx / cols;
		current->col = idx % cols;
		print_single_item(select, current);
		current = current->next;
		idx++;
	}
}

void		select_loop(t_select *select)
{
	t_item	*prev_cursor;
	ssize_t	size_read;
	char	buf[8];
	int		hotkey;

	prev_cursor = select->cursor_item;
	print_select_items(select);
	while (select->cur_items != NULL)
	{
		if (prev_cursor != select->cursor_item
			&& !(prev_cursor->flags & DELETED_FLAG))
			print_single_item(select, prev_cursor);
		prev_cursor = select->cursor_item;
		print_single_item(select, select->cursor_item);
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
