/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   region.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:27:16 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/15 16:07:35 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGION_H
# define REGION_H

# include <string.h>
# include "alloc.h"

typedef struct s_region_list	t_region_list;

/*
** La structure represente une ou plusieurs pages memoires.
** Elle permet de stocker les meta donnees concernant la region memoire.
**
** parent_list est un pointeur vers la liste dans laquelle est contenue
** la region.
** map_size est la taille totale de memoire demandee au systeme.
** region_size est la nombre d'octets de memoire reserves aux allocations.
** ptr_start est l'adresse de debut des allocations.
** prev est un pointeur vers la precedent region d'allocations ou NULL si
** celle-ci se trouve etre la premiere.
** next est un pointeur vers la prochaine region d'allocations ou NULL si
** celle-ci est la derniere.
** free_list est un tableau de pointeur vers les allocations disponibles pour
** chaque niveau de l'arbre binaire.
** data permet la lecture des donnees de chaque allocation.
*/

typedef struct	s_region
{
	t_region_list	*parent_list;
	size_t			map_size;
	size_t			region_size;
	void			*ptr_start;
	struct s_region	*prev;
	struct s_region	*next;
	t_free_alloc	*free_list[17];
	t_alloc_meta	data[0];
}				t_region;

struct			s_region_list
{
	int			quantum_size;
	int			max_order;
	size_t		max_blocks;
	t_region	*head;
};

t_region		*init_malloc_region(t_region_list data);

#endif
