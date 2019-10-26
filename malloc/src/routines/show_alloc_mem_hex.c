/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:15:42 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/25 10:52:33 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "malloc.h"
#include "zone.h"

void	show_alloc_mem_hex_routine(t_zone *zone)
{
	ft_printf("TINY:\n");
	show_region_list_allocs(&zone->tiny_region, 1);
	ft_printf("SMALL:\n");
	show_region_list_allocs(&zone->small_region, 1);
	ft_printf("LARGE:\n");
	show_large_allocs(zone->large_list, 1);
}
