/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:12:28 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/19 21:31:26 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	swap(t_list **lst)
{
	t_list	*elem;

	elem = *lst;
	if (elem == NULL || elem->next == NULL)
		return (1);
	*lst = elem->next;
	elem->next = (*lst)->next;
	(*lst)->next = elem;
	return (1);
}

int	push(t_list **to, t_list **from)
{
	t_list	*elem;

	elem = *from;
	if (elem == NULL)
		return (1);
	*from = elem->next;
	elem->next = *to;
	*to = elem;
	return (1);
}

int	rotate(t_list **lst)
{
	t_list	*head;

	head = *lst;
	if (head == NULL)
		return (1);
	*lst = head->next;
	head->next = NULL;
	ft_lstpush(lst, head);
	return (1);
}

int	rev_rotate(t_list **lst)
{
	t_list	*tail;
	t_list	*prev;

	tail = *lst;
	if (tail == NULL)
		return (1);
	prev = NULL;
	while (tail->next != NULL)
	{
		prev = tail;
		tail = tail->next;
	}
	if (prev != NULL)
	{
		prev->next = NULL;
		tail->next = *lst;
		*lst = tail;
	}
	return (1);
}
