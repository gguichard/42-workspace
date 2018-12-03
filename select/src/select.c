/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 11:42:03 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/03 14:40:21 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "ft_select.h"

static void	set_cols(t_select *select)
{
	t_list	*lst;
	int		count;

	lst = select->options;
	count = 0;
	while (lst != NULL)
	{
		select->col_width = ft_max(ft_strlen(lst->content), select->col_width);
		lst = lst->next;
		count++;
	}
	select->col_width++;
	select->cols = ft_max(1, tgetnum("co") / select->col_width);
	select->rows = (count / select->cols) + (count % select->cols > 0);
	while ((select->cols * select->rows) - count >= select->rows)
	{
		select->cols--;
		select->rows = (count / select->cols) + (count % select->cols > 0);
	}
}

static void	print_choices(t_select *select)
{
	char	*cm;
	t_list	*lst;
	int		index;
	int		col;
	int		row;

	if (!(cm = tgetstr("cm", NULL)))
		return ;
	lst = select->options;
	index = 0;
	while (lst != NULL)
	{
		col = select->col_width * (index % select->cols);
		row = index / select->cols;
		tputs(tgoto(cm, col, row), 1, putchar);
		tputs(lst->content, 1, putchar);
		lst = lst->next;
		index++;
	}
}

void		init_select(t_select *select)
{
	char	*cl;

	if (!(cl = tgetstr("cl", NULL)))
		return ;
	tputs(cl, 1, putchar);
	set_cols(select);
	print_choices(select);
}
