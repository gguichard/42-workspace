/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 09:35:34 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/05 14:10:47 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "ft_select.h"

extern t_select	*g_select;

void			clean_search(void)
{
	free(g_select->search);
	g_select->search = NULL;
	tputs(tgoto(tgetstr("cm", NULL), 0, g_select->back->row + 2)
			, 1, ft_tputchar);
	tputs(tgetstr("dl", NULL), 1, ft_tputchar);
}

void			show_search(void)
{
	if (g_select->search != NULL)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, g_select->back->row + 2)
				, 1, ft_tputchar);
		ft_dprintf(STDERR_FILENO, "Recherche : %s\n", g_select->search);
	}
}

static char		*search_filestr(char *str)
{
	char	*tmp;

	tmp = ft_strchr(str, '/');
	if (tmp == NULL)
		return (str);
	return (tmp + 1);
}

static void		search_levenshtein(t_choice **current)
{
	t_choice	*lst;
	int			lowest_dist;
	t_choice	*lowest_choice;
	int			dist;

	lst = g_select->head;
	lowest_dist = INT_MAX;
	lowest_choice = g_select->head;
	while (lst != NULL)
	{
		dist = ft_levenshtein(search_filestr(lst->content), g_select->search);
		if (dist < lowest_dist)
		{
			lowest_dist = dist;
			lowest_choice = lst;
		}
		lst = lst->next;
		if (lst == g_select->head)
			break ;
	}
	(*current)->cursor = 0;
	lowest_choice->cursor = 1;
	*current = lowest_choice;
	show_search();
}

void			search_choice(t_choice **current, int key)
{
	size_t	len;
	char	*tmp;

	tmp = g_select->search;
	if (!tmp)
		len = 0;
	else
		len = ft_strlen(tmp);
	if ((g_select->search = (char *)malloc(len + 2)) != NULL)
	{
		if (len > 0)
			ft_memcpy(g_select->search, tmp, len);
		(g_select->search)[len] = key;
		(g_select->search)[len + 1] = '\0';
	}
	free(tmp);
	search_levenshtein(current);
}
