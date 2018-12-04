/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 09:55:21 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/04 20:14:40 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft.h"
# include <unistd.h>
# include <term.h>

# define MOVEUP_KEY 4283163
# define MOVEDOWN_KEY 4348699
# define MOVELEFT_KEY 4479771
# define MOVERIGHT_KEY 4414235
# define SPACE_KEY 32
# define ESC_KEY 27
# define ENTER_KEY 10
# define DEL_KEY 127
# define BS_KEY 2117294875

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

void			init_term(void);
void			reset_term(void);

void			init_select(void);
void			print_select(void);

void			listen_keys(void);

void			up_choice(t_choice **current);
void			down_choice(t_choice **current);
void			left_choice(t_choice **current);
void			right_choice(t_choice **current);

void			handle_resize(int signal);
void			handle_pause(int signal);
void			handle_continue(int signal);
void			handle_signal(int signal);

int				ft_tputchar(int c);
void			clean_exit(void);

#endif
