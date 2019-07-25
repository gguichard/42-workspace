/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   region.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:27:16 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/25 09:53:11 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGION_H
# define REGION_H

#include <string.h>
#include "alloc.h"

/*
* La structure represente une ou plusieurs pages memoires.
* Elle permet de stocker les meta donnees concernant la region memoire.
*
* size est la taille de la region de donnee en memoire (celle des allocations,
* donc sans la taille de cette structure).
* ptr_start est l'adresse de debut des allocations.
* next est un pointeur vers la prochaine region d'allocations ou bien NULL
* si celle-ci est la derniere.
* bitmap sera detaillee dans une version future.
*
*/
typedef struct	s_region
{
	size_t			size;
	void			*ptr_start;
	struct s_region	*next;
	t_free_alloc	*free_list[23];
	t_alloc_meta	bitmap[0];
}				t_region;

t_region		*init_malloc_region(void);

#endif
