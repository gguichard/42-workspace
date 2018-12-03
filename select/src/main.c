/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 09:47:47 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/03 14:23:41 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>
#include "ft_select.h"

int				g_run = 1;

static void		free_arg(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

static t_list	*chain_args(int argc, char **argv)
{
	t_list	*args;
	t_list	*elem;
	int		index;

	args = NULL;
	index = 1;
	while (index < argc)
	{
		elem = ft_lstnew(argv[index], ft_strlen(argv[index]) + 1);
		if (elem == NULL)
			return (ft_lstdel(&args, &free_arg));
		ft_lstpush(&args, elem);
		index++;
	}
	return (args);
}

int				main(int argc, char **argv)
{
	t_select	select;

	if (!(select.options = chain_args(argc, argv)))
		return (1);
	else if (tgetent(select.buff, getenv("TERM")) <= 0)
		ft_dprintf(2, "No term entry for %s.\n", getenv("TERM"));
	else
	{
		signal(SIGHUP, &handle_signal);
		tcgetattr(STDIN_FILENO, &(select.term));
		ft_memcpy(&(select.def), &(select.term), sizeof(struct termios));
		select.term.c_lflag &= ~(ICANON | ECHO);
		select.term.c_cc[VMIN] = 1;
		select.term.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &(select.term));
		init_select(&select);
		tcsetattr(STDIN_FILENO, TCSANOW, &(select.def));
	}
	ft_lstdel(&(select.options), &free_arg);
	return (0);
}
