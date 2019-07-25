/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:00:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/25 14:23:22 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "malloc.h"
#include "region.h"
#include "alloc.h"

size_t				get_block_index(t_region *region, t_free_alloc *block)
{
	size_t	block_index;

	block_index = ((uintptr_t)block - (uintptr_t)region->ptr_start);
	block_index /= SMALL_QUANTUM;
	return (block_index);
}

t_region			*get_block_region(t_region *region_list, void *addr)
{
	t_region	*it;

	it = region_list;
	while (it != NULL)
	{
		if (addr >= it->ptr_start && addr < (it->ptr_start + it->size))
		{
			if ((((uintptr_t)addr - (uintptr_t)it->ptr_start)
				& (SMALL_QUANTUM - 1)) != 0)
				it = NULL;
			break ;
		}
		it = it->next;
	}
	return (it);
}

void				add_to_free_list(t_free_alloc **free_list
	, t_free_alloc *free_alloc)
{
	t_free_alloc	*head;

	head = *free_list;
	free_alloc->next = head;
	*free_list = free_alloc;
}

static void			split_block(t_region *region, t_free_alloc *block
	, int level)
{
	size_t			blk_index;
	t_free_alloc	*buddy;

	block->size >>= 1;
	blk_index = get_block_index(region, block);
	buddy = (t_free_alloc *)((char *)block + block->size);
	buddy->size = block->size;
	region->bitmap[blk_index].free = 1;
	region->bitmap[blk_index].size -= 1;
	region->bitmap[get_block_index(region, buddy)] = region->bitmap[blk_index];
	add_to_free_list(region->free_list + level, buddy);
	add_to_free_list(region->free_list + level, block);
}

static t_free_alloc	*get_free_addr(t_region *region, int level)
{
	t_free_alloc	*parent;
	t_free_alloc	*free_addr;

	if (region->free_list[level] == NULL)
	{
		if (level <= 0)
			return (NULL);
		parent = get_free_addr(region, level - 1);
		if (parent == NULL)
			return (NULL);
		split_block(region, parent, level);
	}
	free_addr = region->free_list[level];
	if (free_addr != NULL)
	{
		region->free_list[level] = free_addr->next;
		region->bitmap[get_block_index(region, free_addr)].free = 0;
	}
	return (free_addr);
}

void				*get_free_block_addr(t_region **region_list, int order)
{
	int			level;
	void		*addr;
	t_region	*it;
	t_region	*new_region;

	level = 23 - order;
	addr = NULL;
	it = *region_list;
	while (it != NULL)
	{
		addr = (void *)get_free_addr(it, level);
		if (addr != NULL)
			break ;
		it = it->next;
	}
	if (addr == NULL)
	{
		new_region = init_malloc_region();
		if (new_region == NULL)
			return (NULL);
		new_region->next = *region_list;
		*region_list = new_region;
		addr = (void *)get_free_addr(new_region, level);
	}
	return (addr);
}
