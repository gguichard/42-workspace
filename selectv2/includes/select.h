/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 14:05:23 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/05 14:41:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H

# include "libft.h"
# include <stdlib.h>
# include <string.h>
# include <term.h>
# include <sys/ioctl.h>
# include "items.h"

typedef struct		s_select_format
{
	size_t			col_width;
	unsigned int	max_col;
}					t_select_format;

typedef struct		s_select
{
	int				tty_fd;
	struct termios	def_term;
	struct termios	custom_term;
	struct winsize	winsize;
	t_item			*def_items;
	t_item			*cur_items;
	t_item			*cursor_item;
	t_list			*hotkeys;
	t_select_format	format;
	char			hotkeys_buf[10];
	char			search_query[100];
}					t_select;

int					setup_term(t_select *select);
int					reset_term(t_select *select);
int					update_winsize(t_select *select);

t_select_format		get_columns_format(t_select *select);

void				print_single_item(t_select *select, t_item *item);
void				print_select_items(t_select *select);

void				hotkey_nav_hook(int type);
void				hotkey_del_hook(int type);
void				hotkey_exit_hook(int type);
void				hotkey_select_hook(int type);
void				select_loop(t_select *select);

void				handle_job_signals(int sig);
void				handle_resize_signal(int sig);
void				handle_common_signal(int sig);

int					t_putchar(int c);

#endif
