/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 20:18:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/26 19:17:02 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "malloc.h"
#include "zone.h"
#include "region.h"
#include "alloc.h"

static void	*realloc_copy(t_zone *zone, void *ptr, size_t old_size
	, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	new_ptr = malloc_routine(zone, new_size);
	if (new_ptr != NULL)
	{
		copy_size = old_size;
		if (copy_size > new_size)
			copy_size = new_size;
		ft_memcpy(new_ptr, ptr, copy_size);
	}
	return (new_ptr);
}

static void	*try_to_realloc_large_block(t_zone *zone, void *addr, size_t size)
{
	t_large_block	*large_block;
	void			*new_ptr;

	large_block = search_large_block(zone, addr);
	if (large_block == NULL)
		return (NULL);
	new_ptr = realloc_copy(zone, addr, large_block->user_size, size);
	free_large_block(zone, large_block);
	return (new_ptr);
}

void		*realloc_routine(t_zone *zone, void *ptr, size_t size)
{
	t_region	*region;
	void		*new_ptr;
	size_t		old_size;

	if (ptr == NULL)
		return (malloc_routine(zone, size));
	region = get_block_region(zone->small_region, ptr);
	if (region == NULL)
		return (try_to_realloc_large_block(zone, ptr, size));
	old_size = region->bitmap[get_block_index(region, ptr)].user_size;
	new_ptr = realloc_copy(zone, ptr, old_size, size);
	free_routine(zone, ptr);
	return (new_ptr);
}
