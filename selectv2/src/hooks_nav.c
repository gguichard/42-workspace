/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_nav.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 12:59:00 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/07 15:51:39 by gguichar         ###   ########.fr       */
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

static t_item	*get_item_at_pos(t_select *select, size_t row, size_t col)
{
	t_item	*item;

	item = select->cur_items;
	while (item != NULL
		&& (item->row != row || item->col != col))
		item = item->next;
	return (item);
}

void			hotkey_nav_updown_hook(int type)
{
	t_select	*select;
	t_item		*cursor;
	ssize_t		row;
	ssize_t		col;

	select = g_select;
	cursor = select->cursor_item;
	if (cursor == NULL)
		return ;
	row = cursor->row;
	col = cursor->col;
	if (type == HOTKEY_ARROW_UP)
		row -= 1;
	else if (type == HOTKEY_ARROW_DOWN)
		row += 1;
	if (row < 0 || row > select->format.max_row)
		return ;
	cursor = get_item_at_pos(select, row, col);
	if (cursor != NULL)
		g_select->cursor_item = cursor;
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
