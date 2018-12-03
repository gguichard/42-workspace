/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 11:42:03 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/03 22:34:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "ft_select.h"

static void	compute_cols(t_select *select)
{
	t_choice	*lst;
	int			t_cols;

	lst = select->choices;
	t_cols = tgetnum("co");
	select->col_width = 1;
	while (lst != NULL)
	{
		select->col_width = ft_max(ft_strlen(lst->content), select->col_width);
		lst = lst->next;
	}
	select->col_width += 2;
	select->cols = ft_max(1, t_cols / select->col_width);
	select->col_width += t_cols / select->cols - select->col_width;
}

static void	print_select(t_select *select)
{
	char		*cmotion;
	t_choice	*lst;
	int			index;
	int			col;
	int			diff;

	if (!(cmotion = tgetstr("cm", NULL)))
		return ;
	lst = select->choices;
	index = 0;
	while (lst != NULL)
	{
		col = select->col_width * (index % select->cols);
		tputs(tgoto(cmotion, col, index / select->cols), 1, ft_tputchar);
		diff = select->col_width - ft_strlen(lst->content);
		ft_printf("[%-*s", diff / 2 + diff % 2 - 1, "");
		if (lst->cursor)
			tputs(tgetstr("us", NULL), 1, ft_tputchar);
		if (lst->selected)
			tputs(tparm(tgetstr("AB", NULL), 8), 1, ft_tputchar);
		ft_printf("%s", lst->content);
		if (lst->cursor || lst->selected)
			tputs(tgetstr("me", NULL), 1, ft_tputchar);
		ft_printf("%*s]", diff / 2 - 1, "");
		index++;
		lst = lst->next;
	}
}

void		init_select(t_select *select)
{
	char	*clear;
	char	buff[3];

	if (!(clear = tgetstr("cl", NULL)))
		return ;
	tputs(clear, 1, ft_tputchar);
	compute_cols(select);
	print_select(select);
	while (42)
	{
		read(STDIN_FILENO, &buff, 3);
		handle_keys(select, buff);
		ft_memset(buff, 0, 3);
		print_select(select);
	}
}
