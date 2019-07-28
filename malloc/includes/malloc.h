/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:17:11 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/28 14:22:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <string.h>
# include "region.h"
# include "alloc.h"
# include "zone.h"

# define TINY_QUANTUM 16
# define TINY_MAX_BLOCKS 65536
# define TINY_MAX_ORDER 20

# define SMALL_QUANTUM 512
# define SMALL_MAX_BLOCKS 16384
# define SMALL_MAX_ORDER 23

# define SMALL_THRESHOLD 1024
# define LARGE_THRESHOLD 16384

size_t			align_up(size_t n, int mod);

size_t			get_block_index(t_region *region, t_free_alloc *block);
t_region		*get_block_region(t_zone *zone, void *addr);
t_large_block	*search_large_block(t_zone *zone, void *addr);
void			*get_free_block_addr(t_region_list *region_list, int order
	, size_t user_size);

void			add_to_free_list(t_free_alloc **free_list
	, t_free_alloc *free_alloc);
int				remove_from_free_list(t_free_alloc **free_list
	, t_free_alloc *target);

void			*malloc_routine(t_zone *zone, size_t size);
void			*realloc_routine(t_zone *zone, void *ptr, size_t size);
void			free_large_block(t_zone *zone, t_large_block *large_block);
void			free_routine(t_zone *zone, void *ptr);

void			*malloc(size_t size);
void			*calloc(size_t count, size_t size);
void			*realloc(void *ptr, size_t size);
void			*reallocf(void *ptr, size_t size);
void			free(void *ptr);

#endif
