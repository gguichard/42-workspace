/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choices.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:46:06 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/04 11:48:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_select.h"

extern t_select	*g_select;

static t_choice	*list_new_choice(char *str)
{
	t_choice	*elem;

	if (!(elem = (t_choice *)malloc(sizeof(*elem))))
		return (NULL);
	elem->cursor = 0;
	elem->selected = 0;
	elem->col = 0;
	elem->row = 0;
	elem->content = str;
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

void			clean_choices(void)
{
	t_choice	*lst;

	lst = g_select->head;
	while (lst != NULL)
	{
		free(lst);
		if ((lst = lst->next) == g_select->head)
			break ;
	}
	g_select->head = NULL;
	g_select->back = NULL;
}

int				list_choices(int argc, char **argv)
{
	t_choice	*elem;
	int			index;

	elem = NULL;
	index = 1;
	while (index < argc)
	{
		if (!(elem = list_new_choice(argv[index])))
			return (0);
		else if (g_select->back == NULL)
			g_select->head = elem;
		else
		{
			elem->prev = g_select->back;
			g_select->back->next = elem;
		}
		g_select->back = elem;
		index++;
	}
	g_select->head->prev = g_select->back;
	g_select->back->next = g_select->head;
	return (1);
}
