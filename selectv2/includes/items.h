/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 15:19:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/06 01:00:06 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEMS_H
# define ITEMS_H

# include <sys/stat.h>

# define SELECTED_FLAG (1)
# define DELETED_FLAG (1 << 1)

typedef struct		s_item
{
	size_t			row;
	size_t			col;
	int				flags;
	mode_t			file_mode;
	const char		*content;
	struct s_item	*prev;
	struct s_item	*next;
}					t_item;

t_item				*create_items(int count, char **choices);

#endif
