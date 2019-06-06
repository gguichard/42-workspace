/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 12:58:26 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/06 20:31:45 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "select.h"
#include "items.h"
#include "hotkeys.h"

extern t_select	*g_select;

void			hotkey_nav_hook(int type)
{
	t_item	*cursor;
	t_item	*new_cursor;

	cursor = g_select->cursor_item;
	if (cursor == NULL)
		return ;
	new_cursor = NULL;
	if (type == HOTKEY_ARROW_LEFT)
		new_cursor = cursor->prev;
	else if (type == HOTKEY_ARROW_RIGHT)
		new_cursor = cursor->next;
	if (new_cursor == NULL)
	{
		new_cursor = g_select->cur_items;
		if (type == HOTKEY_ARROW_LEFT)
		{
			while (new_cursor->next != NULL)
				new_cursor = new_cursor->next;
		}
	}
	g_select->cursor_item = new_cursor;
}

void			hotkey_del_hook(int type)
{
	t_item	*cursor;
	t_item	*new_cursor;

	if (type == HOTKEY_BACKSPACE && del_search_char(g_select))
		return ;
	cursor = g_select->cursor_item;
	if (cursor == NULL)
		return ;
	if (g_select->cur_items == cursor)
		g_select->cur_items = cursor->next;
	new_cursor = (cursor->next != NULL ? cursor->next : cursor->prev);
	g_select->cursor_item = new_cursor;
	if (cursor->prev != NULL)
		cursor->prev->next = cursor->next;
	if (cursor->next != NULL)
		cursor->next->prev = cursor->prev;
	cursor->flags &= ~SELECTED_FLAG;
	cursor->flags |= DELETED_FLAG;
	print_select_items(g_select);
}

void			hotkey_exit_hook(int type)
{
	t_item	*lst;
	int		is_first;

	if (type == HOTKEY_ENTER)
	{
		lst = g_select->cur_items;
		is_first = 1;
		while (lst != NULL)
		{
			if (lst->flags & SELECTED_FLAG)
				ft_printf("%s%s", (is_first ? "" : " "), lst->content);
			lst = lst->next;
			is_first = 0;
		}
	}
}

void			hotkey_select_hook(int type)
{
	t_item	*cursor;

	if (type == HOTKEY_SPACE)
	{
		del_whole_search(g_select);
		cursor = g_select->cursor_item;
		if (cursor == NULL)
			return ;
		cursor->flags ^= SELECTED_FLAG;
		if (cursor->next != NULL)
			g_select->cursor_item = cursor->next;
		else
			g_select->cursor_item = g_select->cur_items;
	}
}

static int		should_unselect_all(t_select *select)
{
	t_item	*item;

	item = select->cur_items;
	while (item != NULL)
	{
		if (!(item->flags & SELECTED_FLAG))
			return (0);
		item = item->next;
	}
	return (1);
}

void			hotkey_select_all_hook(int type)
{
	t_item	*item;
	int		unselect;
	int		prev;

	if (type == HOTKEY_CTRL_A)
	{
		item = g_select->cur_items;
		unselect = should_unselect_all(g_select);
		while (item != NULL)
		{
			prev = item->flags;
			if (unselect)
				item->flags &= ~SELECTED_FLAG;
			else
				item->flags |= SELECTED_FLAG;
			if (item->flags != prev)
				print_single_item(g_select, item);
			item = item->next;
		}
	}
}

void			hotkey_home_end_hook(int type)
{
	t_item	*item;

	if (type == HOTKEY_HOME)
		g_select->cursor_item = g_select->cur_items;
	else if (type == HOTKEY_END)
	{
		item = g_select->cursor_item;
		while (item != NULL && item->next != NULL)
			item = item->next;
		g_select->cursor_item = item;
	}
}
