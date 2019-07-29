/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:18:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/29 14:18:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "malloc.h"
#include "zone.h"

t_zone			g_def_zone = (t_zone){
	(t_region_list){
		TINY_QUANTUM,
		TINY_MAX_ORDER,
		TINY_MAX_BLOCKS,
		NULL
	},
	(t_region_list){
		SMALL_QUANTUM,
		SMALL_MAX_ORDER,
		SMALL_MAX_BLOCKS,
		NULL
	},
	NULL
};
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

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
	if (size < LARGE_THRESHOLD)
		ft_memset(ptr, 0, total_size);
	return (ptr);
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
	else if (size == 0)
		return (16);
	else
		return (1 << (int)ceil(log2(size)));
}

void	show_alloc_mem(void)
{
	pthread_mutex_lock(&g_mutex);
	show_alloc_mem_routine(&g_def_zone);
	pthread_mutex_unlock(&g_mutex);
}
