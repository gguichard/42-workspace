/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 09:55:21 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/04 08:56:48 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft.h"
# include <unistd.h>
# include <term.h>

typedef struct	s_choice
{
	int				cursor;
	int				selected;
	int				col;
	int				row;
	char			*content;
	struct s_choice	*prev;
	struct s_choice	*next;
}				t_choice;

typedef struct	s_select
{
	struct s_choice	*head;
	struct s_choice	*back;
	struct termios	def;
	struct termios	term;
	int				col_width;
	int				cols;
}				t_select;

int				ft_tputchar(int c);

void			handle_signal(int signal);

void			init_select(t_select *select);

void			handle_keys(t_select *select, char *buf);

#endif
