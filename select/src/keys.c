/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 22:25:10 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/04 09:34:47 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "ft_select.h"

static void	select_choice(t_choice **current)
{
	(*current)->selected = !(*current)->selected;
}

static void	up_choice(t_choice **current)
{
	t_choice	*tmp;

	tmp = *current;
	tmp->cursor = 0;
	tmp = tmp->prev;
	while (tmp->col != (*current)->col)
		tmp = tmp->prev;
	tmp->cursor = 1;
	*current = tmp;
}

static void	down_choice(t_choice **current)
{
	t_choice	*tmp;

	tmp = *current;
	tmp->cursor = 0;
	tmp = tmp->next;
	while (tmp->col != (*current)->col)
		tmp = tmp->next;
	tmp->cursor = 1;
	*current = tmp;
}

static void	prev_choice(t_choice **current)
{
	t_choice	*tmp;

	tmp = *current;
	tmp->cursor = 0;
	if (tmp->prev->row == tmp->row)
		tmp = tmp->prev;
	else
	{
		while (tmp->next->row == tmp->row)
			tmp = tmp->next;
	}
	tmp->cursor = 1;
	*current = tmp;
}

static void	next_choice(t_choice **current)
{
	t_choice	*tmp;

	tmp = *current;
	tmp->cursor = 0;
	if (tmp->next->row == tmp->row)
		tmp = tmp->next;
	else
	{
		while (tmp->prev->row == tmp->row)
			tmp = tmp->prev;
	}
	tmp->cursor = 1;
	*current = tmp;
}

void		handle_keys(t_select *select, char *buf)
{
	static t_choice	*current = NULL;

	if (current == NULL)
		current = select->head;
	if (buf[0] == ' ')
		select_choice(&current);
	if (buf[0] == 0x1B && buf[1] == '[')
	{
		if (buf[2] == 'D')
			prev_choice(&current);
		else if (buf[2] == 'C')
			next_choice(&current);
		else if (buf[2] == 'A')
			up_choice(&current);
		else if (buf[2] == 'B')
			down_choice(&current);
	}
}
