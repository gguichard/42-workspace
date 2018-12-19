/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:12:28 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/19 19:24:28 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	swap(t_list **lst)
{
	t_list	*elem;

	elem = *lst;
	if (elem == NULL || elem->next == NULL)
		return ;
	*lst = elem->next;
	elem->next = (*lst)->next;
	(*lst)->next = elem;
}

void	push(t_list **to, t_list **from)
{
	t_list	*elem;

	elem = *from;
	if (elem == NULL)
		return ;
	*from = elem->next;
	elem->next = *to;
	*to = elem;
}

void	rotate(t_list **lst)
{
	t_list	*head;

	head = *lst;
	if (head == NULL)
		return ;
	*lst = head->next;
	ft_lstpush(lst, head);
}

void	rev_rotate(t_list **lst)
{
	t_list	*tail;
	t_list	*prev;

	tail = *lst;
	if (tail == NULL)
		return ;
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
}
