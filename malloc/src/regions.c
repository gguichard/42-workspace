/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:02:10 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/28 14:52:48 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include "malloc.h"
#include "region.h"
#include "alloc.h"

t_region	*init_malloc_region(t_region_list data)
{
	size_t			region_meta_size;
	size_t			region_data_size;
	size_t			region_map_size;
	t_region		*region;
	t_free_alloc	*block;

	region_meta_size = align_up(sizeof(t_region)
		+ sizeof(t_alloc_meta) * data.max_blocks, 16);
	region_data_size = data.quantum_size * data.max_blocks;
	region_map_size = align_up(region_meta_size + region_data_size
			, getpagesize());
	region = (t_region *)mmap(NULL, region_map_size, PROT_READ | PROT_WRITE
			, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if ((void *)region == MAP_FAILED)
		return (NULL);
	block = (t_free_alloc *)((char *)region + region_meta_size);
	block->next = NULL;
	region->map_size = region_map_size;
	region->region_size = region_data_size;
	region->ptr_start = block;
	region->next = NULL;
	region->free_list[0] = block;
	region->bitmap[0].free = 1;
	region->bitmap[0].order = data.max_order;
	return (region);
}
