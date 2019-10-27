/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 22:49:14 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/27 16:54:29 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "malloc.h"
#include "zone.h"

extern t_zone			g_def_zone;
extern pthread_mutex_t	g_mutex;

void	malloc_constructor(void)
{
	if (getenv("MallocDumpAtExit") != NULL)
		atexit(show_alloc_mem);
}

size_t	malloc_size(const void *ptr)
{
	size_t	size;

	if (ptr == NULL)
		return (0);
	pthread_mutex_lock(&g_mutex);
	size = malloc_size_routine(&g_def_zone, ptr);
	pthread_mutex_unlock(&g_mutex);
	return (size);
}

size_t	malloc_good_size(size_t size)
{
	if (size >= LARGE_THRESHOLD)
		return (size);
	else
		return (1 << order_from_size(size, TINY_QUANTUM));
}

void	show_alloc_mem(void)
{
	pthread_mutex_lock(&g_mutex);
	show_alloc_mem_routine(&g_def_zone);
	pthread_mutex_unlock(&g_mutex);
}

void	show_alloc_mem_hex(void)
{
	pthread_mutex_lock(&g_mutex);
	show_alloc_mem_hex_routine(&g_def_zone);
	pthread_mutex_unlock(&g_mutex);
}
