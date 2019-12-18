/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:15:42 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/18 12:06:58 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include "printf.h"
#include "malloc.h"
#include "zone.h"
#include "region.h"
#include "alloc.h"

extern t_zone	g_def_zone;

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

static void	show_region_allocs(t_region *region, int hex_dump
	, size_t *user_total, size_t *real_total)
{
	size_t			block_index;
	t_alloc_meta	*alloc_meta;
	void			*start_ptr;
	void			*end_ptr;

	block_index = 0;
	while (block_index < region->parent_list->max_blocks)
	{
		alloc_meta = &region->data[block_index];
		if (alloc_meta->free == 0 && alloc_meta->order != 0)
		{
			start_ptr = (void *)((uintptr_t)region->ptr_start
					+ (uintptr_t)(block_index
						* region->parent_list->quantum_size));
			end_ptr = (void *)((uintptr_t)start_ptr
					+ (uintptr_t)(1UL << alloc_meta->order));
			*user_total += alloc_meta->user_size;
			*real_total += (1UL << alloc_meta->order);
			ft_printf("%p - %p: %zu (%zu) bytes\n", start_ptr, end_ptr
				, alloc_meta->user_size, (1UL << alloc_meta->order));
			if (hex_dump)
				dump_alloc_hex(start_ptr, end_ptr);
		}
		block_index++;
	}
}

static void	show_region_list_allocs(t_region_list *region_list, int hex_dump
	, size_t *user_total, size_t *real_total)
{
	t_region	*it;

	it = region_list->head;
	while (it != NULL)
	{
		if (region_list == &g_def_zone.tiny_region)
			ft_printf("TINY: %p\n", it);
		else if (region_list == &g_def_zone.small_region)
			ft_printf("SMALL: %p\n", it);
		show_region_allocs(it, hex_dump, user_total, real_total);
		it = it->next;
	}
}

static void	show_large_allocs(t_large_block *large_list, int hex_dump
	, size_t *user_total, size_t *real_total)
{
	t_large_block	*it;
	void			*start_ptr;
	void			*end_ptr;

	it = large_list;
	while (it != NULL)
	{
		*user_total += it->user_size;
		*real_total += it->map_size;
		ft_printf("LARGE: %p\n", it);
		start_ptr = (void *)(it + 1);
		end_ptr = (void *)((uintptr_t)(it + 1) + (uintptr_t)it->user_size);
		ft_printf("%p - %p: %zu (%zu) bytes\n", start_ptr, end_ptr
			, it->user_size, it->map_size);
		if (hex_dump)
			dump_alloc_hex(start_ptr, end_ptr);
		it = it->next;
	}
}

void		show_alloc_mem_routine(t_zone *zone, int hex_dump)
{
	size_t	user_total;
	size_t	real_total;

	user_total = 0;
	real_total = 0;
	show_region_list_allocs(&zone->tiny_region, hex_dump
		, &user_total, &real_total);
	show_region_list_allocs(&zone->small_region, hex_dump
		, &user_total, &real_total);
	show_large_allocs(zone->large_list, hex_dump, &user_total, &real_total);
	ft_printf("TOTAL: %zu (%zu) bytes\n", user_total, real_total);
}
