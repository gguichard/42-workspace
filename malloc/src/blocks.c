/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:00:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/29 13:56:09 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "malloc.h"
#include "region.h"
#include "alloc.h"

size_t				get_block_index(t_region *region, const t_free_alloc *block)
{
	return (((uintptr_t)block - (uintptr_t)region->ptr_start)
		/ region->parent_list->quantum_size);
}

static t_region		*get_block_region_of_list(t_region_list *region_list
	, const void *addr)
{
	t_region	*it;

	it = region_list->head;
	while (it != NULL)
	{
		if (addr >= it->ptr_start && addr < (it->ptr_start + it->region_size))
		{
			if ((((uintptr_t)addr - (uintptr_t)it->ptr_start)
				& (region_list->quantum_size - 1)) != 0)
				it = NULL;
			break ;
		}
		it = it->next;
	}
	return (it);
}

t_region			*get_block_region(t_zone *zone, const void *addr)
{
	t_region	*region;

	region = get_block_region_of_list(&zone->tiny_region, addr);
	if (region == NULL)
		region = get_block_region_of_list(&zone->small_region, addr);
	return (region);
}

t_large_block		*search_large_block(t_zone *zone, const void *addr)
{
	void			*real_addr;
	t_large_block	*it;

	if (((uintptr_t)addr & (sizeof(t_large_block) - 1)) != 0)
		return (NULL);
	real_addr = ((t_large_block *)addr) - 1;
	it = zone->large_list;
	while (it != NULL)
	{
		if (it == real_addr)
			return (it);
		it = it->next;
	}
	return (NULL);
}

void				add_to_free_list(t_free_alloc **free_list
	, t_free_alloc *free_alloc)
{
	t_free_alloc	*head;

	head = *free_list;
	free_alloc->next = head;
	*free_list = free_alloc;
}

int					remove_from_free_list(t_free_alloc **free_list
	, t_free_alloc *target)
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

static void			split_block(t_region *region, t_free_alloc *block
	, int level)
{
	size_t			block_index;
	t_free_alloc	*buddy;
	size_t			buddy_index;

	block_index = get_block_index(region, block);
	region->bitmap[block_index].free = 1;
	region->bitmap[block_index].order -= 1;
	buddy = (t_free_alloc *)((uintptr_t)block
			+ (uintptr_t)(1 << region->bitmap[block_index].order));
	buddy_index = get_block_index(region, buddy);
	region->bitmap[buddy_index] = region->bitmap[block_index];
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

static t_region		*push_new_region(t_region_list *region_list)
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
		push_new_region(region_list);
	it = region_list->head;
	while (it != NULL)
	{
		addr = get_free_addr(it, level);
		if (addr != NULL)
			break ;
		it = it->next;
		if (it == NULL)
			it = push_new_region(region_list);
	}
	if (addr != NULL)
		it->bitmap[get_block_index(it, addr)].user_size = user_size;
	return (addr);
}
