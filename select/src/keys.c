/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 22:25:10 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/03 22:32:52 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	select_choice(t_choice **current)
{
	(*current)->selected = !(*current)->selected;
}

static void	prev_choice(t_choice **current)
{
	t_choice	*tmp;

	tmp = *current;
	tmp->cursor = 0;
	*current = tmp->prev;
	if (*current == NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		*current = tmp;
	}
	(*current)->cursor = 1;
}

static void	next_choice(t_choice **current)
{
	t_choice	*tmp;

	tmp = *current;
	tmp->cursor = 0;
	*current = tmp->next;
	if (*current == NULL)
	{
		while (tmp->prev != NULL)
			tmp = tmp->prev;
		*current = tmp;
	}
	(*current)->cursor = 1;
}

void		handle_keys(t_select *select, char *buf)
{
	static t_choice	*current = NULL;

	if (current == NULL)
		current = select->choices;
	if (buf[0] == ' ')
		select_choice(&current);
	if (buf[0] == 0x1B && buf[1] == '[')
	{
		if (buf[2] == 'D')
			prev_choice(&current);
		else if (buf[2] == 'C')
			next_choice(&current);
	}
}
