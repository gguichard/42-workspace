/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 14:05:23 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/03 16:28:07 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H

# include <term.h>
# include "items.h"

typedef struct		s_select_format
{
	int				elems;
	int				max_col_width;
	int				max_col;
	int				max_row;
}					t_select_format;

typedef struct		s_select
{
	struct termios	def_term;
	struct termios	custom_term;
	t_item			*def_items;
	t_item			*cur_items;
	t_select_format	format;
	char			search_query[100];
}					t_select;

int					apply_termios(struct termios *term);
int					setup_term(t_select *select);

#endif
