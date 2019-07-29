/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 20:17:25 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/29 17:28:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <sys/mman.h>
#include "malloc.h"
#include "zone.h"
#include "region.h"
#include "alloc.h"

static int					free_region(t_region *region)
{
	region->prev->next = region->next;
	if (region->next != NULL)
		region->next->prev = region->prev;
	munmap(region, region->map_size);
	return (1);
}

static inline t_free_alloc	*get_block_buddy(t_region *region
	, t_free_alloc *block, int order)
{
	return ((t_free_alloc *)((((uintptr_t)block - (uintptr_t)region->ptr_start)
				^ (1 << order)) + (uintptr_t)region->ptr_start));
}

static int					coalesce_block_with_buddy(t_region *region
	, t_free_alloc *block, int order)
{
	int				free_level;
	t_free_alloc	*buddy;
	size_t			blk_idx;

	free_level = region->parent_list->max_order - order;
	if (free_level == 0 && region->prev != NULL)
		return (free_region(region));
	else if (free_level > 0)
	{
		buddy = get_block_buddy(region, block, order);
		blk_idx = get_block_index(region, buddy);
		if (region->bitmap[blk_idx].free
			&& region->bitmap[blk_idx].order == order
			&& remove_from_free_list(region->free_list + free_level, buddy))
		{
			blk_idx = get_block_index(region, (block < buddy ? buddy : block));
			((uint64_t *)&region->bitmap[blk_idx])[0] = 0;
			block = (block < buddy ? block : buddy);
			region->bitmap[get_block_index(region, block)].order = ++order;
			return (coalesce_block_with_buddy(region, block, order));
		}
	}
	region->bitmap[get_block_index(region, block)].free = 1;
	add_to_free_list(region->free_list + free_level, block);
	return (0);
}

void						free_large_block(t_zone *zone
	, t_large_block *large_block)
{
	if (large_block->prev == NULL)
		zone->large_list = NULL;
	else
	{
		large_block->prev->next = large_block->next;
		if (large_block->next != NULL)
			large_block->next->prev = large_block->prev;
	}
	munmap(large_block, large_block->map_size);
}

void						free_routine(t_zone *zone, void *ptr)
{
	t_region		*region;
	t_large_block	*large_block;
	size_t			block_index;
	int				order;

	if (ptr == NULL)
		return ;
	region = get_block_region(zone, ptr);
	if (region == NULL)
	{
		large_block = search_large_block(zone, ptr);
		if (large_block != NULL)
			free_large_block(zone, large_block);
		return ;
	}
	block_index = get_block_index(region, ptr);
	if (region->bitmap[block_index].order == 0
		|| region->bitmap[block_index].free)
		return ;
	order = region->bitmap[block_index].order;
	coalesce_block_with_buddy(region, (t_free_alloc *)ptr, order);
}
