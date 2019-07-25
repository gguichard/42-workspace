/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 20:17:25 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/25 23:00:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "malloc.h"
#include "zone.h"
#include "region.h"
#include "alloc.h"

static int	coalesce_block_with_buddy(t_region *region, t_free_alloc *block
	, int order)
{
	int				free_level;
	t_free_alloc	*buddy;
	size_t			buddy_index;
	t_free_alloc	*parent;
	t_free_alloc	*parent_buddy;

	free_level = 23 - order;
	buddy = (t_free_alloc *)((((uintptr_t)block - (uintptr_t)region->ptr_start)
				^ (1 << order)) + (uintptr_t)region->ptr_start);
	buddy_index = get_block_index(region, buddy);
	if (region->bitmap[buddy_index].free
		&& region->bitmap[buddy_index].order == order
		&& remove_from_free_list(region->free_list + free_level, buddy))
	{
		parent = (block < buddy ? block : buddy);
		parent_buddy = (parent == block ? buddy : block);
		region->bitmap[get_block_index(region, parent)].order = ++order;
		buddy_index = get_block_index(region, parent_buddy);
		((uint8_t *)&region->bitmap[buddy_index])[0] = 0;
		return (coalesce_block_with_buddy(region, parent, order));
	}
	region->bitmap[get_block_index(region, block)].free = 1;
	add_to_free_list(region->free_list + free_level, block);
	return (0);
}

void		free_routine(t_zone *zone, void *ptr)
{
	t_region	*region;
	size_t		block_index;
	int			order;

	if (ptr == NULL)
		return ;
	region = get_block_region(zone->small_region, ptr);
	if (region == NULL)
		return ;
	block_index = get_block_index(region, ptr);
	if (region->bitmap[block_index].order == 0
		|| region->bitmap[block_index].free)
		return ;
	order = region->bitmap[block_index].order;
	coalesce_block_with_buddy(region, (t_free_alloc *)ptr, order);
}
