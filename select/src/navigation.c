/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 12:07:59 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/04 20:11:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	up_choice(t_choice **current)
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

void	down_choice(t_choice **current)
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

void	left_choice(t_choice **current)
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

void	right_choice(t_choice **current)
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
