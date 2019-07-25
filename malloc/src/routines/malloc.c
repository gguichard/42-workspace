/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 20:16:45 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/25 22:51:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include "malloc.h"
#include "zone.h"

void	*malloc_routine(t_zone *zone, size_t size)
{
	int		order;
	void	*ptr;

	order = (int)ceil(log2(size < SMALL_QUANTUM ? SMALL_QUANTUM : size));
	ptr = get_free_block_addr(&zone->small_region, order, size);
	return (ptr);
}
