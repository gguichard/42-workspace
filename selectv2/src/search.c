/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 14:52:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/07 10:53:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <term.h>
#include "select.h"

static void	update_search(t_select *select)
{
	t_item	*current;
	t_item	*next;
	int		dist_left;
	int		dist_right;

	current = select->cur_items;
	while (current != NULL && current->next != NULL)
	{
		next = current->next;
		dist_left = ft_levenshtein(current->content, select->search_query);
		dist_right = ft_levenshtein(next->content, select->search_query);
		if (dist_left <= dist_right)
			current = next;
		else
		{
			swap_list_nodes(select, current, next);
			current = (next->prev == NULL ? select->cur_items : next->prev);
		}
	}
	select->cursor_item = select->cur_items;
	print_select_items(select);
}

void		do_search(t_select *select, char c)
{
	size_t	len;

	if (!ft_isprint(c))
		return ;
	len = ft_strlen(select->search_query);
	if (len + 1 >= sizeof(select->search_query))
		return ;
	select->search_query[len] = c;
	select->search_query[len + 1] = '\0';
	update_search(select);
}

int			del_search_char(t_select *select)
{
	size_t	len;

	len = ft_strlen(select->search_query);
	if (len == 0)
		return (0);
	select->search_query[--len] = '\0';
	if (len == 0)
		print_select_items(select);
	else
		update_search(select);
	return (1);
}

int			del_whole_search(t_select *select)
{
	if (select->search_query[0] == '\0')
		return (0);
	ft_memset(select->search_query, '\0', sizeof(select->search_query));
	print_select_items(select);
	return (1);
}

void		print_search_query(t_select *select, size_t row)
{
	static char	*cm_tcap = NULL;

	if (cm_tcap == NULL)
		cm_tcap = tgetstr("cm", NULL);
	if (row < select->winsize.ws_row && select->search_query[0] != '\0')
	{
		tputs(tgoto(cm_tcap, 0, row), 1, t_putchar);
		ft_dprintf(select->tty_fd, "Recherche : %s\n", select->search_query);
	}
}
