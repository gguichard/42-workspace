/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:00:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/15 16:08:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "malloc.h"
#include "region.h"
#include "alloc.h"

static void			split_block(t_region *region, t_free_alloc *block
	, int level)
{
	size_t			block_index;
	t_free_alloc	*buddy;
	size_t			buddy_index;

	block_index = get_block_index(region, block);
	region->data[block_index].free = 1;
	region->data[block_index].order -= 1;
	buddy = (t_free_alloc *)((uintptr_t)block
			+ (uintptr_t)(1 << region->data[block_index].order));
	buddy_index = get_block_index(region, buddy);
	region->data[buddy_index] = region->data[block_index];
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
		region->data[get_block_index(region, free_addr)].free = 0;
	}
	return (free_addr);
}

static t_region		*map_region(t_region_list *region_list)
{
	t_region	*region;

	region = init_malloc_region(*region_list);
	if (region != NULL)
	{
		region->parent_list = region_list;
		region->prev = NULL;
		region->next = region_list->head;
		if (region->next != NULL)
			region->next->prev = region;
		region_list->head = region;
	}
	return (region);
}

void				*get_free_block_addr(t_region_list *region_list, int order
	, size_t user_size)
{
	int				level;
	t_free_alloc	*addr;
	t_region		*it;

	level = region_list->max_order - order;
	addr = NULL;
	if (region_list->head == NULL)
		map_region(region_list);
	it = region_list->head;
	while (it != NULL)
	{
		addr = get_free_addr(it, level);
		if (addr != NULL)
			break ;
		it = it->next;
		if (it == NULL)
			it = map_region(region_list);
	}
	if (addr != NULL)
		it->data[get_block_index(it, addr)].user_size = user_size;
	return (addr);
}
