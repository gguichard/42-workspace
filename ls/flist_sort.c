/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flist_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 15:50:46 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/25 18:55:30 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_flist	*flist_merge_sort(t_flist *left, t_flist *right
		, int (*cmp)(t_flist *, t_flist *))
{
	t_flist	*lst;
	t_flist	*tmp;
	t_flist	**which;
	t_flist	*tail;

	lst = NULL;
	tail = NULL;
	while (left != NULL || right != NULL)
	{
		if (left == NULL)
			which = &right;
		else if (right == NULL)
			which = &left;
		else
			which = (cmp(left, right) < 0) ? &left : &right;
		tmp = (*which)->next;
		if (!(tail))
			lst = *which;
		else
			tail->next = *which;
		tail = *which;
		*which = tmp;
	}
	return (lst);
}

t_flist			*flist_sort(t_flist *lst, int (*cmp)(t_flist *, t_flist *))
{
	t_flist	*left;
	t_flist	*right;
	t_flist	*tmp;
	t_flist	**which;
	int		count;

	left = NULL;
	right = NULL;
	count = 0;
	while (lst != NULL)
	{
		tmp = lst->next;
		which = (count % 2 == 0) ? &left : &right;
		lst->next = *which;
		*which = lst;
		lst = tmp;
		count++;
	}
	if (count <= 1)
		return (left);
	left = flist_sort(left, cmp);
	right = flist_sort(right, cmp);
	return (flist_merge_sort(left, right, cmp));
}

void		flist_push_back(t_flist **lst, t_flist *elem)
{
	t_flist	*current;

	current = *lst;
	if (current == NULL)
		*lst = elem;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = elem;
	}
}

void		flist_sort_insert(t_flist **lst, t_flist *elem
		, int (*cmp)(t_flist *, t_flist *))
{
	t_flist	*previous;
	t_flist	*current;

	previous = NULL;
	current = *lst;
	while (current != NULL)
	{
		if (cmp(current, elem) >= 0)
			break ;
		previous = current;
		current = current->next;
	}
	elem->next = current;
	if (previous == NULL)
		*lst = elem;
	else
		previous->next = elem;
}
