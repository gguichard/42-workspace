/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 22:25:10 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/05 11:21:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "printf.h"
#include "ft_select.h"

extern t_select	*g_select;

static void		exit_select(void)
{
	int			first;
	t_choice	*lst;

	first = 1;
	reset_term();
	lst = g_select->head;
	while (lst != NULL)
	{
		if (lst->selected)
		{
			ft_printf("%s%s", (first) ? "" : " ", lst->content);
			first = 0;
		}
		lst = lst->next;
		if (lst == g_select->head)
			break ;
	}
	clean_choices();
	clean_search();
	exit(0);
}

static void		del_choice(t_choice **current)
{
	t_choice	*tmp;

	tmp = *current;
	if (tmp->next == tmp)
		clean_exit(0);
	if (g_select->head == tmp)
		g_select->head = tmp->next;
	if (g_select->back == tmp)
		g_select->back = tmp->prev;
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	tmp->next->cursor = 1;
	*current = tmp->next;
	free(tmp);
	init_select();
}

static void		toggle_choice(t_choice **current)
{
	t_choice	*tmp;

	tmp = *current;
	tmp->selected = !(tmp->selected);
	if (tmp->selected)
	{
		tmp->cursor = 0;
		tmp->next->cursor = 1;
		*current = tmp->next;
	}
	clean_search();
}

static int		handle_special_key(int key, t_choice **current)
{
	if (key == ENTER_KEY)
		exit_select();
	else if (key == ESC_KEY)
		clean_exit(0);
	else if (key == DEL_KEY || key == BS_KEY)
		del_choice(current);
	else if (key == SPACE_KEY)
		toggle_choice(current);
	else if (key == MOVEUP_KEY)
		up_choice(current);
	else if (key == MOVEDOWN_KEY)
		down_choice(current);
	else if (key == MOVELEFT_KEY)
		left_choice(current);
	else if (key == MOVERIGHT_KEY)
		right_choice(current);
	else
		return (0);
	return (1);
}

void			listen_keys(void)
{
	static t_choice	*current = NULL;
	int				key;

	if (current == NULL)
		current = g_select->head;
	key = 0;
	read(STDIN_FILENO, &key, 4);
	if (handle_special_key(key, &current))
		clean_search();
	else
		search_choice(&current, key);
}
