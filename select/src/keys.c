/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 22:25:10 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/04 17:55:21 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "printf.h"
#include "ft_select.h"

extern t_select	*g_select;

static void		toggle_choice(t_choice **current)
{
	t_choice	*tmp;

	tmp = *current;
	tmp->selected = !(tmp->selected);
	tmp->cursor = 0;
	tmp->next->cursor = 1;
	*current = tmp->next;
}

static void		exit_select(void)
{
	t_choice	*lst;
	size_t		count;

	reset_term();
	lst = g_select->head;
	count = 0;
	while (lst != NULL)
	{
		if (lst->selected)
		{
			ft_printf("%s%s", (count == 0) ? "" : " ", lst->content);
			count++;
		}
		lst = lst->next;
		if (lst == g_select->head)
			break ;
	}
	clean_choices();
	exit(0);
}

static void		del_choice(t_choice **current)
{
	t_choice	*tmp;

	tmp = *current;
	if (tmp->next == tmp)
	{
		handle_signal(SIGINT);
		return ;
	}
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

void			listen_keys(void)
{
	static t_choice	*current = NULL;
	int				key;

	if (current == NULL)
		current = g_select->head;
	key = 0;
	read(STDIN_FILENO, &key, 4);
	if (key == ENTER_KEY)
		exit_select();
	else if (key == ESC_KEY)
		handle_signal(SIGINT);
	else if (key == DEL_KEY || key == BS_KEY)
		del_choice(&current);
	else if (key == SPACE_KEY)
		toggle_choice(&current);
	else if (key == MOVEUP_KEY)
		up_choice(&current);
	else if (key == MOVEDOWN_KEY)
		down_choice(&current);
	else if (key == MOVELEFT_KEY)
		prev_choice(&current);
	else if (key == MOVERIGHT_KEY)
		next_choice(&current);
}
