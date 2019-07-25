/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:18:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/25 14:33:57 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "libft.h"
#include "malloc.h"
#include "zone.h"
#include "region.h"

t_zone			g_def_zone;
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

static void	*malloc_routine(t_zone *zone, size_t size)
{
	int		order;
	void	*ptr;

	order = (int)ceil(log2(size < SMALL_QUANTUM ? SMALL_QUANTUM : size));
	ptr = get_free_block_addr(&zone->small_region, order);
	return (ptr);
}

void	*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = malloc_routine(&g_def_zone, size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

void	*calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = count * size;
	if (count != 0 && total_size / count != size)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	ptr = malloc_routine(&g_def_zone, total_size);
	pthread_mutex_unlock(&g_mutex);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}

static int	remove_free_block(t_free_alloc **free_list, t_free_alloc *target)
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

static int	coalesce_block_with_buddy(t_region *region, t_free_alloc *block
	, int order)
{
	int				free_level;
	t_free_alloc	*buddy;
	size_t			buddy_index;
	t_free_alloc	*parent;
	t_free_alloc	*parent_buddy;

	free_level = 23 - order;
	buddy = (t_free_alloc *)((((uintptr_t)block - (uintptr_t)region->ptr_start)
				^ (1 << order)) + (uintptr_t)region->ptr_start);
	buddy_index = get_block_index(region, buddy);
	if (region->bitmap[buddy_index].free
		&& region->bitmap[buddy_index].size == order
		&& remove_free_block(region->free_list + free_level, buddy))
	{
		parent = (block < buddy ? block : buddy);
		parent_buddy = (parent == block ? buddy : block);
		region->bitmap[get_block_index(region, parent)].size = ++order;
		buddy_index = get_block_index(region, parent_buddy);
		((uint8_t *)region->bitmap)[buddy_index] = 0;
		return (coalesce_block_with_buddy(region, parent, order));
	}
	block->size = (1 << order);
	region->bitmap[get_block_index(region, block)].free = 1;
	add_to_free_list(region->free_list + free_level, block);
	return (0);
}

static void	free_routine(t_zone *zone, void *ptr)
{
	t_region	*region;
	size_t		block_index;
	int			order;

	if (ptr == NULL)
		return ;
	region = get_block_region(zone->small_region, ptr);
	if (region == NULL)
		return ;
	block_index = get_block_index(region, ptr);
	if (region->bitmap[block_index].size == 0
		|| region->bitmap[block_index].free)
		return ;
	order = region->bitmap[block_index].size;
	coalesce_block_with_buddy(region, (t_free_alloc *)ptr, order);
}

static void	*realloc_routine(t_zone *zone, void *ptr, size_t size)
{
	t_region	*region;
	void		*new_ptr;
	size_t		copy_size;
	size_t		block_index;

	if (ptr == NULL)
		return (malloc_routine(zone, size));
	region = get_block_region(zone->small_region, ptr);
	if (region == NULL)
		return (NULL);
	block_index = get_block_index(region, ptr);
	copy_size = (1 << region->bitmap[block_index].size);
	if (copy_size > size)
		copy_size = size;
	new_ptr = malloc_routine(zone, size);
	if (new_ptr != NULL)
		ft_memcpy(new_ptr, ptr, copy_size);
	free_routine(zone, ptr);
	return (new_ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	pthread_mutex_lock(&g_mutex);
	new_ptr = realloc_routine(&g_def_zone, ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (new_ptr);
}

void	*reallocf(void *ptr, size_t size)
{
	void	*new_ptr;

	pthread_mutex_lock(&g_mutex);
	new_ptr = realloc_routine(&g_def_zone, ptr, size);
	if (new_ptr == NULL)
		free_routine(&g_def_zone, ptr);
	pthread_mutex_unlock(&g_mutex);
	return (new_ptr);
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	free_routine(&g_def_zone, ptr);
	pthread_mutex_unlock(&g_mutex);
}
