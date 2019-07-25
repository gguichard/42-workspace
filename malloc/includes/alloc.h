/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 12:56:40 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/24 20:42:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include <inttypes.h>

typedef struct	s_alloc_meta
{
	uint8_t		free:1;
	uint8_t		size:7;
}				t_alloc_meta;

typedef struct	s_free_alloc
{
	size_t				size;
	struct s_free_alloc	*next;
}				t_free_alloc;

#endif
