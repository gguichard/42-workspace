/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 09:55:21 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/04 12:12:39 by gguichar         ###   ########.fr       */
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

void			clean_choices(void);

int				list_choices(int argc, char **argv);

void			reset_term(void);

void			init_select(void);

void			handle_keys(char *buf);

void			up_choice(t_choice **current);
void			down_choice(t_choice **current);
void			prev_choice(t_choice **current);
void			next_choice(t_choice **current);

void			handle_signal(int signal);

int				ft_tputchar(int c);

#endif
