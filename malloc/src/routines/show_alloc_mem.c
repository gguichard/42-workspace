/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:15:42 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/25 10:49:58 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include "printf.h"
#include "malloc.h"
#include "zone.h"
#include "region.h"
#include "alloc.h"

static void	dump_alloc_hex(void *start_ptr, void *end_ptr)
{
	size_t	idx;
	uint8_t	byte;
	char	buffer[48];

	while ((start_ptr + 16) <= end_ptr)
	{
		idx = 0;
		while (idx < 16)
		{
			byte = ((uint8_t *)start_ptr)[idx];
			buffer[idx * 3] = "0123456789abcdef"[byte >> 4];
			buffer[idx * 3 + 1] = "0123456789abcdef"[byte & 0xf];
			buffer[idx * 3 + 2] = ' ';
			idx++;
		}
		buffer[sizeof(buffer) - 1] = '\0';
		ft_printf("%p: %s\n", start_ptr, buffer);
		start_ptr += 16;
	}
	write(STDOUT_FILENO, "\n", 1);
}

static void	show_region_allocs(t_region *region, int dump_hex)
{
	size_t			block_index;
	t_alloc_meta	*alloc_meta;
	void			*start_ptr;
	void			*end_ptr;

	block_index = 0;
	while (block_index < region->parent_list->max_blocks)
	{
		alloc_meta = &region->bitmap[block_index];
		if (alloc_meta->free == 0 && alloc_meta->order != 0)
		{
			start_ptr = (void *)((uintptr_t)region->ptr_start
					+ (uintptr_t)(block_index
						* region->parent_list->quantum_size));
			end_ptr = (void *)((uintptr_t)start_ptr
					+ (uintptr_t)(1UL << alloc_meta->order));
			ft_printf("%p - %p: %zu (%zu) bytes\n", start_ptr, end_ptr
				, alloc_meta->user_size, (1UL << alloc_meta->order));
			if (dump_hex)
				dump_alloc_hex(start_ptr, end_ptr);
		}
		block_index++;
	}
}

void		show_region_list_allocs(t_region_list *region_list, int dump_hex)
{
	t_region	*it;

	it = region_list->head;
	while (it != NULL)
	{
		show_region_allocs(it, dump_hex);
		it = it->next;
	}
}

void		show_large_allocs(t_large_block *large_list, int dump_hex)
{
	t_large_block	*it;
	void			*start_ptr;
	void			*end_ptr;

	it = large_list;
	while (it != NULL)
	{
		start_ptr = (void *)(it + 1);
		end_ptr = (void *)((uintptr_t)(it + 1) + (uintptr_t)it->user_size);
		ft_printf("%p - %p: %zu (%zu) bytes\n", start_ptr, end_ptr
			, it->user_size, it->map_size);
		if (dump_hex)
			dump_alloc_hex(start_ptr, end_ptr);
		it = it->next;
	}
}

void		show_alloc_mem_routine(t_zone *zone)
{
	ft_printf("TINY:\n");
	show_region_list_allocs(&zone->tiny_region, 0);
	ft_printf("SMALL:\n");
	show_region_list_allocs(&zone->small_region, 0);
	ft_printf("LARGE:\n");
	show_large_allocs(zone->large_list, 0);
}
