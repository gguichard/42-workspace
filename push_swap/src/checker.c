/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:38:40 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/24 13:51:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "parsing.h"
#include "checker.h"

static void	init_checker(t_checker *checker, int argc, char **argv)
{
	checker->argc = argc;
	checker->argv = argv;
	checker->fd = 0;
	checker->a = NULL;
	checker->b = NULL;
}

static int	setup_checker(t_opt *opt, t_checker *checker)
{
	int	offset;

	if (has_opt(opt, FILE_OPT))
	{
		checker->fd = open(get_optarg(opt, FILE_OPT), O_RDONLY);
		if (checker->fd < 0)
		{
			ft_dprintf(2, "checker: %s: unable to open file\n"
					, get_optarg(opt, FILE_OPT));
			return (0);
		}
	}
	if (checker->argc > 0)
	{
		offset = create_list(&(checker->a), checker->argc, checker->argv);
		if (offset < 0)
			return (show_error());
		checker->argc -= offset;
		checker->argv += offset;
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_checker	checker;
	t_opt		*opt;

	init_checker(&checker, argc, argv);
	opt = parse_opts(argc, argv, VALID_OPT);
	if (has_opt(opt, HELP_OPT) || (opt->error != 0 && !ft_isdigit(opt->error)))
		return (show_help(opt));
	checker.argc -= opt->index;
	checker.argv += opt->index;
	if (setup_checker(opt, &checker))
	{
		if (!apply_rots(&checker))
			show_error();
		else if (check_lists(&checker))
			ft_printf("OK\n");
		else
			ft_dprintf(2, "KO\n");
		ft_lstfree(&(checker.a));
		ft_lstfree(&(checker.b));
	}
	if (has_opt(opt, FILE_OPT) && checker.fd >= 0)
		close(checker.fd);
	return (0);
}
