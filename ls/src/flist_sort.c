/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flist_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 15:50:46 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/28 11:10:15 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_flist	*flist_merge_sort(t_flist *left, t_flist *right
		, int (*cmp)(t_flist *, t_flist *), int cmp_mul)
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
			which = (cmp_mul * cmp(left, right) < 0) ? &left : &right;
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

t_flist			*flist_sort(t_flist *lst
		, int (*cmp)(t_flist *, t_flist *), int cmp_mul)
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
	left = flist_sort(left, cmp, cmp_mul);
	right = flist_sort(right, cmp, cmp_mul);
	return (flist_merge_sort(left, right, cmp, cmp_mul));
}

void			flist_sort_insert(t_flist **lst, t_flist *file
		, int (*cmp)(t_flist *, t_flist *), int cmp_mul)
{
	t_flist	*previous;
	t_flist	*current;

	previous = NULL;
	current = *lst;
	while (current != NULL)
	{
		if (cmp_mul * cmp(current, file) >= 0)
			break ;
		previous = current;
		current = current->next;
	}
	file->next = current;
	if (previous == NULL)
		*lst = file;
	else
		previous->next = file;
}
