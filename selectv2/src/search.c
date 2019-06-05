/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 14:52:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/05 23:46:09 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <term.h>
#include "select.h"

static void	swap_list_nodes(t_select *select, t_item *left, t_item *right)
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
	select->search_query[len - 1] = '\0';
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
