/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 15:19:25 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/03 15:47:35 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "items.h"

static int	get_next_item_index(t_item *items, int count, int offset)
{
	int	idx;

	idx = offset;
	while (idx < count)
	{
		if (!(items[idx].flags & DELETED_FLAG))
			return (idx);
		idx++;
	}
	return (-1);
}

void		chain_items(t_item *items, int count)
{
	int		idx;
	t_item	*current;
	int		next_index;
	t_item	*next;

	idx = 0;
	while (idx < count)
	{
		current = items + idx;
		next_index = get_next_item_index(items, count, idx + 1);
		if (next_index == -1)
		{
			items->prev = current;
			current->next = items;
			break ;
		}
		next = items + next_index;
		current->next = next;
		next->prev = current;
		idx = next_index;
	}
}

t_item		*create_items(int count, char **choices)
{
	t_item		*items;
	int			idx;
	struct stat	file_stat;

	items = (t_item *)ft_memalloc(sizeof(t_item) * count);
	if (items != NULL)
	{
		idx = 0;
		while (idx < count)
		{
			items[idx].content = choices[idx];
			if (stat(choices[idx], &file_stat) != -1)
				items[idx].file_mode = file_stat.st_mode;
			idx++;
		}
		chain_items(items, count);
	}
	return (items);
}
