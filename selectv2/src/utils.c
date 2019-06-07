/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 22:33:52 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/07 10:52:23 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "select.h"

extern t_select	*g_select;

int				t_putchar(int c)
{
	return (write(g_select->tty_fd, &c, 1));
}

void			swap_list_nodes(t_select *select, t_item *left, t_item *right)
{
	right->prev = left->prev;
	if (right->prev == NULL)
		select->cur_items = right;
	else
		right->prev->next = right;
	if (right->next != NULL)
		right->next->prev = left;
	left->prev = right;
	left->next = right->next;
	right->next = left;
}
