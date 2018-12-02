/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 09:47:47 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/02 15:04:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <term.h>

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
		elem = ft_lstnew(argv[index], ft_strlen(argv[index]));
		if (elem == NULL)
			return (ft_lstdel(&args, &free_arg));
		ft_lstpush(&args, elem);
		index++;
	}
	return (args);
}

int				main(int argc, char **argv)
{
	t_list			*lst;
	char			*buff;
	struct termios	term;

	if (!(lst = chain_args(argc, argv)))
		ft_dprintf(2, "Error while parsing args.\n");
	else if (!(buff = (char *)malloc(2048 * sizeof(char))))
		ft_dprintf(2, "Unable to malloc buffer.\n");
	else if (tgetent(buff, getenv("TERM")) <= 0)
		ft_dprintf(2, "No term entry for %s.\n", getenv("TERM"));
	else
	{
		signal(SIGHUP, &handle_signal);
		show_select(lst);
		tcgetattr(STDIN_FILENO, &term);

		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		while (read(0, NULL, 1)) ;
	}
	ft_lstdel(&lst, &free_arg);
	return (0);
}
