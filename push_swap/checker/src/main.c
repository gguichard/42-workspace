/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:38:40 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/20 12:41:45 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "checker.h"

static void	init_checker(t_checker *checker, int argc, char **argv)
{
	checker->argc = argc - 1;
	checker->argv = argv + 1;
	checker->options = 0;
	checker->fd = 0;
	checker->a = NULL;
	checker->b = NULL;
}

static int	setup_checker(t_checker *checker)
{
	if (checker->options & FILE_OPT)
	{
		if (checker->argc == 0)
			return (show_help());
		checker->fd = open(checker->argv[0], O_RDONLY);
		if (checker->fd < 0)
		{
			ft_dprintf(2, "checker: %s: unable to open file\n"
					, checker->argv[0]);
			return (0);
		}
		checker->argc--;
		checker->argv++;
	}
	if (checker->argc == 0)
		return (1);
	checker->a = create_list(checker);
	if (checker->a == NULL)
		return (show_error());
	return (1);
}

int			main(int argc, char **argv)
{
	t_checker	checker;

	init_checker(&checker, argc, argv);
	if (!parse_options(&checker) || checker.options & HELP_OPT)
		return (show_help());
	if (setup_checker(&checker))
	{
		if (!apply_sets(&checker))
			return (show_error());
		if (check_lists(&checker))
			ft_printf("OK\n");
		else
			ft_dprintf(2, "KO\n");
	}
	if (checker.options & FILE_OPT && checker.fd >= 0)
		close(checker.fd);
	return (0);
}
