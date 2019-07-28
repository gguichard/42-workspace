/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:15:42 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/28 21:56:15 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "printf.h"
#include "malloc.h"
#include "zone.h"
#include "region.h"
#include "alloc.h"

static void	show_region_allocs(t_region *region)
{
	size_t	block_index;
	void	*start_ptr;
	void	*end_ptr;

	block_index = 0;
	while (block_index < region->parent_list->max_blocks)
	{
		if (region->bitmap[block_index].free == 0
			&& region->bitmap[block_index].order != 0)
		{
			start_ptr = (void *)((uintptr_t)region->ptr_start
					+ (uintptr_t)(block_index
						* region->parent_list->quantum_size));
			end_ptr = (void *)((uintptr_t)start_ptr
					+ (uintptr_t)region->bitmap[block_index].user_size);
			ft_printf("%p - %p: %zu (%zu) bytes\n", start_ptr, end_ptr
				, region->bitmap[block_index].user_size
				, (1 << region->bitmap[block_index].order));
		}
		block_index++;
	}
}

static void	show_region_list_allocs(t_region_list *region_list)
{
	t_region	*it;

	it = region_list->head;
	while (it != NULL)
	{
		show_region_allocs(it);
		it = it->next;
	}
}

static void	show_large_allocs(t_large_block *large_list)
{
	t_large_block	*it;

	it = large_list;
	while (it != NULL)
	{
		ft_printf("%p - %p: %zu (%zu) bytes\n", it + 1
			, (void *)((uintptr_t)(it + 1) + (uintptr_t)it->user_size)
			, it->user_size, it->map_size);
		it = it->next;
	}
}

void		show_alloc_mem_routine(t_zone *zone)
{
	ft_printf("TINY:\n");
	show_region_list_allocs(&zone->tiny_region);
	ft_printf("SMALL:\n");
	show_region_list_allocs(&zone->small_region);
	ft_printf("LARGE:\n");
	show_large_allocs(zone->large_list);
}
