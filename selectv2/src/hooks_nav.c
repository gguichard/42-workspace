/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_nav.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 12:59:00 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/07 13:00:50 by gguichar         ###   ########.fr       */
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
