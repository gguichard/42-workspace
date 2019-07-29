/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 13:49:06 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/29 22:52:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "malloc.h"
#include "zone.h"
#include "region.h"
#include "alloc.h"

size_t	malloc_size_routine(t_zone *zone, const void *ptr)
{
	t_region		*region;
	t_large_block	*large_block;

	region = get_block_region(zone, ptr);
	if (region == NULL)
	{
		large_block = search_large_block(zone, ptr);
		return (large_block == NULL ? 0 : large_block->map_size
			- sizeof(t_large_block));
	}
	return (1 << region->bitmap[get_block_index(region, ptr)].order);
}
