/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 10:55:44 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/17 12:28:40 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "alloc_list.h"
#include "utils.h"

alloc_list_t	*push_alloc(alloc_list_t **lst, void *data)
{
	alloc_list_t	*node = malloc(sizeof(alloc_list_t));

	if (node == NULL)
		exit_unexpected();
	node->data = data;
	node->next = *lst;
	*lst = node;
	return node;
}

void			del_alloc_list(alloc_list_t **lst, void (*fn)(void *))
{
	alloc_list_t	*node;
	alloc_list_t	*next;

	for (node = *lst; node != NULL; node = next)
	{
		next = node->next;
		if (fn != NULL)
			fn(node->data);
		free(node);
	}
	*lst = NULL;
}
