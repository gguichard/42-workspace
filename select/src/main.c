/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 09:47:47 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/03 21:16:30 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>
#include "ft_select.h"

static void		*clean_choices(t_choice *lst)
{
	t_choice	*choice;

	while (lst != NULL)
	{
		choice = lst->next;
		free(lst);
		lst = choice;
	}
	return (NULL);
}

static t_choice	*list_choices(int argc, char **argv)
{
	t_choice	*choices;
	t_choice	*elem;
	t_choice	*prev;
	int			index;

	choices = NULL;
	elem = NULL;
	index = 1;
	while (index < argc)
	{
		prev = elem;
		if (!(elem = (t_choice *)malloc(sizeof(*elem))))
			return (clean_choices(choices));
		elem->cursor = (prev == NULL);
		elem->selected = 0;
		elem->content = argv[index];
		elem->prev = prev;
		elem->next = NULL;
		if (prev == NULL)
			choices = elem;
		else
			prev->next = elem;
		index++;
	}
	return (choices);
}

int				main(int argc, char **argv)
{
	t_select	select;

	if (!(select.choices = list_choices(argc, argv)))
		return (1);
	else if (tgetent(NULL, getenv("TERM")) <= 0)
		ft_dprintf(2, "No term entry for %s.\n", getenv("TERM"));
	else
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
	}
	clean_choices(select.choices);
	return (0);
}
