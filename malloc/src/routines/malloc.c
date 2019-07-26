/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 20:16:45 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/26 19:02:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <math.h>
#include "malloc.h"
#include "zone.h"
#include "alloc.h"

static void	*malloc_large_block(t_zone *zone, size_t size)
{
	size_t			map_size;
	t_large_block	*large_block;

	map_size = align_up(size + sizeof(t_large_block), getpagesize());
	large_block = mmap(NULL, map_size, PROT_READ | PROT_WRITE
			, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if ((void *)large_block == MAP_FAILED)
		return (NULL);
	large_block->map_size = map_size;
	large_block->user_size = size;
	large_block->next = zone->large_list;
	if (large_block->next != NULL)
		large_block->next->prev = large_block;
	large_block->prev = NULL;
	zone->large_list = large_block;
	return ((void *)(large_block + 1));
}

void		*malloc_routine(t_zone *zone, size_t size)
{
	void	*ptr;
	int		order;

	if (size > SMALL_THRESHOLD)
		ptr = malloc_large_block(zone, size);
	else
	{
		order = (int)ceil(log2(size < SMALL_QUANTUM ? SMALL_QUANTUM : size));
		ptr = get_free_block_addr(&zone->small_region, order, size);
	}
	return (ptr);
}
