/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 22:43:03 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/29 22:46:19 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "malloc.h"
#include "region.h"
#include "alloc.h"
#include "zone.h"

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
