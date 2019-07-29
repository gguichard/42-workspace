/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 22:43:37 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/29 22:45:15 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "malloc.h"
#include "alloc.h"

void	add_to_free_list(t_free_alloc **free_list, t_free_alloc *free_alloc)
{
	t_free_alloc	*head;

	head = *free_list;
	free_alloc->next = head;
	*free_list = free_alloc;
}

int		remove_from_free_list(t_free_alloc **free_list, t_free_alloc *target)
{
	t_free_alloc	*prev;
	t_free_alloc	*it;

	prev = NULL;
	it = *free_list;
	while (it != target)
	{
		if (it == NULL)
			return (0);
		prev = it;
		it = it->next;
	}
	if (prev == NULL)
		*free_list = target->next;
	else
		prev->next = target->next;
	return (1);
}
