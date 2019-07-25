/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:02:10 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/25 14:15:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include "malloc.h"
#include "region.h"
#include "alloc.h"

t_region	*init_malloc_region(void)
{
	size_t			region_header_size;
	size_t			region_data_size;
	t_region		*region;
	t_free_alloc	*block;

	region_header_size = align_up(sizeof(t_region)
		+ sizeof(t_alloc_meta) * SMALL_MAX_NODES, 16);
	region_data_size = SMALL_QUANTUM * SMALL_MAX_BLOCKS;
	region = (t_region *)mmap(NULL
		, align_up(region_header_size + region_data_size, getpagesize())
		, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if ((void *)region == MAP_FAILED)
		return (NULL);
	block = (t_free_alloc *)((char *)region + region_header_size);
	block->size = region_data_size;
	block->next = NULL;
	region->size = region_data_size;
	region->ptr_start = block;
	region->next = NULL;
	region->free_list[0] = block;
	region->bitmap[0].free = 1;
	region->bitmap[0].size = 23; // log2(SMALL_QUANTUM * SMALL_MAX_BLOCKS)
	return (region);
}
