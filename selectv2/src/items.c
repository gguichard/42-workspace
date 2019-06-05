/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 15:19:25 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/06 01:00:13 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "items.h"

static void	chain_items(t_item *items, int count)
{
	int		idx;
	t_item	*current;

	idx = 0;
	while (idx < count)
	{
		current = items + idx;
		if (idx + 1 < count)
		{
			current->next = items + idx + 1;
			current->next->prev = current;
		}
		idx++;
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
