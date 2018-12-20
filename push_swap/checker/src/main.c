/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:38:40 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/20 12:27:11 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "checker.h"

static void	setup_checker(t_checker *checker)
{
	checker->options = 0;
	checker->file = NULL;
	checker->fd = 0;
	checker->a = NULL;
	checker->b = NULL;
}

static int	show_error(void)
{
	ft_dprintf(2, "Error\n");
	return (0);
}

static int	show_help(void)
{
	ft_printf("usage: checker [-%s] numbers ...\n", VALID_OPT);
	ft_printf("\tf [path] - read instructions from file\n");
	ft_printf("\tv - verbose mode\n");
	ft_printf("\th - show this help\n");
	return (0);
}

static int	run_checker(t_checker *checker)
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

	setup_checker(&checker);
	checker.argc = argc - 1;
	checker.argv = argv + 1;
	if (!parse_options(&checker) || checker.options & HELP_OPT)
		return (show_help());
	if (run_checker(&checker))
	{
		if (apply_sets(&checker) && check_lists(&checker))
			ft_printf("OK\n");
		else
			ft_dprintf(2, "KO\n");
	}
	if (checker.options & FILE_OPT && checker.fd >= 0)
		close(checker.fd);
	return (0);
}
