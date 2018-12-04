/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 11:42:03 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/04 12:02:43 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "ft_select.h"

extern t_select	*g_select;

static int		compute_col_width(void)
{
	t_choice	*lst;
	int			col_width;

	col_width = 1;
	lst = g_select->head;
	while (lst != NULL)
	{
		col_width = ft_max(ft_strlen(lst->content), col_width);
		if ((lst = lst->next) == g_select->head)
			break ;
	}
	return (col_width + 2);
}

static void		compute_cols(void)
{
	t_choice	*lst;
	int			t_cols;
	int			index;

	t_cols = tgetnum("co");
	g_select->col_width = compute_col_width();
	g_select->cols = ft_max(1, t_cols / g_select->col_width);
	index = 0;
	lst = g_select->head;
	while (lst != NULL)
	{
		lst->col = g_select->col_width * (index % g_select->cols);
		lst->row = index / g_select->cols;
		if ((lst = lst->next) == g_select->head)
			break ;
		index++;
	}
}

static void		print_choice(t_choice *choice)
{
	static char	*cmotion = NULL;
	int			diff;

	if (cmotion == NULL)
		cmotion = tgetstr("cm", NULL);
	tputs(tgoto(cmotion, choice->col, choice->row), 1, ft_tputchar);
	diff = g_select->col_width - ft_strlen(choice->content);
	ft_putchar('[');
	if (choice->cursor)
		tputs(tgetstr("us", NULL), 1, ft_tputchar);
	if (choice->selected)
		tputs(tparm(tgetstr("AB", NULL), 8), 1, ft_tputchar);
	ft_printf("%*s", diff / 2 + diff % 2 - 1, "");
	ft_putstr(choice->content);
	ft_printf("%-*s", diff / 2 - 1, "");
	if (choice->cursor || choice->selected)
		tputs(tgetstr("me", NULL), 1, ft_tputchar);
	ft_putchar(']');
}

static void		print_select(void)
{
	t_choice	*lst;

	lst = g_select->head;
	while (lst != NULL)
	{
		print_choice(lst);
		if ((lst = lst->next) == g_select->head)
			break ;
	}
}

void			init_select(void)
{
	char	*clear;
	char	buff[3];

	if (!(clear = tgetstr("cl", NULL)))
		return ;
	tputs(clear, 1, ft_tputchar);
	compute_cols();
	g_select->head->cursor = 1;
	print_select();
	while (42)
	{
		read(STDIN_FILENO, &buff, 3);
		handle_keys(buff);
		ft_memset(buff, 0, 3);
		print_select();
	}
}
