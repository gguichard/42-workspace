/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 12:56:40 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/26 19:00:13 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include <inttypes.h>

typedef struct	s_alloc_meta
{
	uint8_t		free:1;
	uint8_t		order:7;
	uint64_t	user_size:56;
}				t_alloc_meta;

typedef struct	s_free_alloc
{
	struct s_free_alloc	*next;
}				t_free_alloc;

typedef struct	s_large_block
{
	size_t					map_size;
	size_t					user_size;
	struct s_large_block	*prev;
	struct s_large_block	*next;
}				t_large_block;

#endif
