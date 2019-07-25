/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 20:18:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/25 22:55:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "malloc.h"
#include "zone.h"
#include "region.h"

void	*realloc_routine(t_zone *zone, void *ptr, size_t size)
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
	copy_size = region->bitmap[block_index].user_size;
	if (copy_size > size)
		copy_size = size;
	new_ptr = malloc_routine(zone, size);
	if (new_ptr != NULL)
		ft_memcpy(new_ptr, ptr, copy_size);
	free_routine(zone, ptr);
	return (new_ptr);
}
