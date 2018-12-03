/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 09:55:21 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/03 14:21:56 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft.h"
# include <unistd.h>
# include <term.h>

typedef struct	s_select
{
	t_list			*options;
	char			buff[2048];
	struct termios	def;
	struct termios	term;
	int				rows;
	int				cols;
	int				col_width;
	int				cur_row;
	int				cur_col;
}				t_select;

void			handle_signal(int signal);

void			init_select(t_select *select);

#endif
