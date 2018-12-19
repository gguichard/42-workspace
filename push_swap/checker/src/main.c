/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:38:40 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/20 00:51:51 by gguichar         ###   ########.fr       */
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
	return (1);
}

static int	show_help(const char *name)
{
	ft_printf("usage: %s [-%s] numbers ...\n", name, VALID_OPT);
	ft_printf("\tf [path] - read instructions from file\n");
	ft_printf("\tv - verbose mode\n");
	ft_printf("\th - show this help\n");
	return (0);
}

int			main(int argc, char **argv)
{
	t_checker	checker;

	checker.argc = argc - 1;
	checker.argv = argv + 1;
	setup_checker(&checker);
	if (!parse_options(&checker))
		return (show_error());
	if (checker.options & HELP_OPT)
		return (show_help(argv[0]));
	if (checker.options & FILE_OPT)
	{
		checker.file = checker.argv[0];
		checker.argc--;
		checker.argv++;
	}
	if (checker.argc > 0 && (checker.a = create_list(&checker)) == NULL)
		return (show_error());
	if (checker.options & FILE_OPT)
	{
		checker.fd = open(checker.file, O_RDONLY);
		if (checker.fd < 0)
		{
			ft_dprintf(2, "%s: %s: unable to open file\n"
					, argv[0], checker.file);
			return (1);
		}
	}
	if (!apply_sets(&checker) || !check_lists(&checker))
	{
		ft_dprintf(2, "KO\n");
		return (1);
	}
	ft_printf("OK\n");
	return (0);
}
