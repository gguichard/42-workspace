/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 11:42:03 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/04 23:46:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <stdlib.h>
#include "printf.h"
#include "ft_select.h"

extern t_select	*g_select;

static int		get_col_width(void)
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
	return (col_width + 4);
}

static void		compute_cols(void)
{
	struct winsize	ws;
	int				index;
	t_choice		*lst;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) < 0)
	{
		ft_dprintf(2, "ft_select: unable to get columns\n");
		clean_exit(1);
	}
	g_select->col_width = get_col_width();
	g_select->cols = ft_max(1, ws.ws_col / g_select->col_width);
	index = 0;
	lst = g_select->head;
	while (lst != NULL)
	{
		lst->col = g_select->col_width * (index % g_select->cols);
		lst->row = index / g_select->cols;
		lst = lst->next;
		if (lst == g_select->head)
			break ;
		index++;
	}
}

void			init_select(void)
{
	static char	*clear = NULL;

	if (clear == NULL)
		clear = tgetstr("cl", NULL);
	if (clear == NULL)
	{
		ft_dprintf(2, "ft_select: unable to get clear str\n");
		clean_exit(1);
	}
	compute_cols();
	tputs(clear, 1, ft_tputchar);
}

static void		print_choice(t_choice *choice)
{
	static char	*cmotion = NULL;
	int			diff;

	if (cmotion == NULL)
		cmotion = tgetstr("cm", NULL);
	if (cmotion == NULL)
	{
		ft_dprintf(2, "ft_select: unable to get cursor motion str\n");
		clean_exit(1);
	}
	tputs(tgoto(cmotion, choice->col, choice->row), 1, ft_tputchar);
	diff = g_select->col_width - ft_strlen(choice->content);
	ft_putchar_fd('[', STDERR_FILENO);
	if (choice->cursor)
		tputs(tgetstr("us", NULL), 1, ft_tputchar);
	if (choice->selected)
		tputs(tparm(tgetstr("AB", NULL), 8), 1, ft_tputchar);
	ft_dprintf(STDERR_FILENO, "%*s", diff / 2 + diff % 2 - 1, "");
	ft_dprintf(STDERR_FILENO, choice->content);
	ft_dprintf(STDERR_FILENO, "%-*s", diff / 2 - 1, "");
	if (choice->cursor || choice->selected)
		tputs(tgetstr("me", NULL), 1, ft_tputchar);
	ft_putchar_fd(']', STDERR_FILENO);
}

void			print_select(void)
{
	t_choice	*lst;

	lst = g_select->head;
	while (lst != NULL)
	{
		print_choice(lst);
		lst = lst->next;
		if (lst == g_select->head)
			break ;
	}
}
