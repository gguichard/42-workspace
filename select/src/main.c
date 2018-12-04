/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 09:47:47 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/04 09:31:49 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>
#include "ft_select.h"

static void		clean_choices(t_select *select)
{
	t_choice	*lst;

	lst = select->head;
	while (lst->next != select->head)
	{
		free(lst);
		lst = lst->next;
	}
	select->head = NULL;
	select->back = NULL;
}

static t_choice	*list_new_choice(char *str)
{
	t_choice	*elem;

	if (!(elem = (t_choice *)malloc(sizeof(*elem))))
		return (NULL);
	elem->cursor = 0;
	elem->selected = 0;
	elem->col = 0;
	elem->row = 0;
	elem->content = str;
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

static int		list_choices(t_select *select, int argc, char **argv)
{
	t_choice	*elem;
	int			index;

	elem = NULL;
	index = 1;
	while (index < argc)
	{
		if (!(elem = list_new_choice(argv[index])))
		{
			clean_choices(select);
			return (0);
		}
		if (select->back == NULL)
			select->head = elem;
		else
		{
			elem->prev = select->back;
			select->back->next = elem;
		}
		select->back = elem;
		index++;
	}
	select->head->prev = select->back;
	select->back->next = select->head;
	return (1);
}

int				main(int argc, char **argv)
{
	t_select	select;

	if (argc <= 1)
	{
		ft_dprintf(2, "usage: ./ft_select [args...]\n");
		return (1);
	}
	if (tgetent(NULL, getenv("TERM")) <= 0)
	{
		ft_dprintf(2, "ft_select: no term entry for %s\n", getenv("TERM"));
		return (1);
	}
	select.head = NULL;
	select.back = NULL;
	if (list_choices(&select, argc, argv))
	{
		//signal(SIGHUP, &handle_signal);
		tcgetattr(STDIN_FILENO, &(select.term));
		ft_memcpy(&(select.def), &(select.term), sizeof(struct termios));
		select.term.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &(select.term));
		tputs(tgetstr("vi", NULL), 1, ft_tputchar);
		tputs(tgetstr("ti", NULL), 1, ft_tputchar);
		init_select(&select);
		tcsetattr(STDIN_FILENO, TCSANOW, &(select.def));
		tputs(tgetstr("ve", NULL), 1, ft_tputchar);
		tputs(tgetstr("te", NULL), 1, ft_tputchar);
		clean_choices(&select);
	}
	return (0);
}
