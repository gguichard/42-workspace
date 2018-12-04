/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 09:47:47 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/04 12:12:21 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>
#include "ft_select.h"

t_select		*g_select;

int				catch_errors(int argc)
{
	if (argc <= 1)
		ft_dprintf(2, "usage: ./ft_select [args...]\n");
	else if (tgetent(NULL, getenv("TERM")) <= 0)
		ft_dprintf(2, "ft_select: no term entry for %s\n", getenv("TERM"));
	else if (!(g_select = (t_select *)malloc(sizeof(*g_select))))
		ft_dprintf(2, "ft_select: malloc error\n");
	else
		return (0);
	return (1);
}

void			reset_term(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_select->def));
	tputs(tgetstr("ve", NULL), 1, ft_tputchar);
	tputs(tgetstr("te", NULL), 1, ft_tputchar);
	clean_choices();
}

int				main(int argc, char **argv)
{
	if (catch_errors(argc))
		return (1);
	g_select->head = NULL;
	g_select->back = NULL;
	if (list_choices(argc, argv))
	{
		signal(SIGTERM, &handle_signal);
		signal(SIGINT, &handle_signal);
		signal(SIGQUIT, &handle_signal);
		tcgetattr(STDIN_FILENO, &(g_select->term));
		ft_memcpy(&(g_select->def), &(g_select->term), sizeof(struct termios));
		g_select->term.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &(g_select->term));
		tputs(tgetstr("vi", NULL), 1, ft_tputchar);
		tputs(tgetstr("ti", NULL), 1, ft_tputchar);
		init_select();
	}
	return (0);
}
