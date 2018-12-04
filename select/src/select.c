/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 11:42:03 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/04 09:32:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "ft_select.h"

static void	compute_cols(t_select *select)
{
	t_choice	*lst;
	int			t_cols;
	int			index;

	t_cols = tgetnum("co");
	select->col_width = 1;
	lst = select->head;
	while (lst->next != select->head)
	{
		select->col_width = ft_max(ft_strlen(lst->content), select->col_width);
		lst = lst->next;
	}
	select->col_width += 2;
	select->cols = ft_max(1, t_cols / select->col_width);
	select->col_width += t_cols / select->cols - select->col_width;
	index = 0;
	lst = select->head;
	while (lst->next != select->head)
	{
		lst->col = select->col_width * (index % select->cols);
		lst->row = index / select->cols;
		lst = lst->next;
		index++;
	}
}

static void	print_select(t_select *select)
{
	char		*cmotion;
	t_choice	*lst;
	int			diff;

	if (!(cmotion = tgetstr("cm", NULL)))
		return ;
	lst = select->head;
	while (lst->next != select->head)
	{
		tputs(tgoto(cmotion, lst->col, lst->row), 1, ft_tputchar);
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
	select->head->cursor = 1;
	print_select(select);
	while (42)
	{
		read(STDIN_FILENO, &buff, 3);
		handle_keys(select, buff);
		ft_memset(buff, 0, 3);
		print_select(select);
	}
}
