/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 09:12:29 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/25 21:37:06 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

static void	invalid_opt(char c)
{
	ft_dprintf(2, "ft_ls: illegal option -- %c\n", c);
	ft_dprintf(2, "usage: ft_ls [-%s] [file ...]\n", VALID_OPTIONS);
	exit(1);
}

static void	parse_column_opt(t_opt *opt)
{
	opt->options |= COL_OPT;
	opt->options &= ~ONE_OPT;
}

static void	parse_1_opt(t_opt *opt)
{
	opt->options |= ONE_OPT;
	opt->options &= ~COL_OPT;
}

static void	parse_opt(t_opt *opt, char c)
{
	if (c == 'C')
		parse_column_opt(opt);
	else if (c == '1')
		parse_1_opt(opt);
	else
	{
		opt->options |= opt_mask(c);
	}
}

int			parse_options(t_opt *opt, int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	opt->options = 0;
	while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0')
	{
		j = 1;
		while (argv[i][j] != '\0')
		{
			if (!ft_strchr(VALID_OPTIONS, argv[i][j]))
				invalid_opt(argv[i][j]);
			parse_opt(opt, argv[i][j]);
			j++;
		}
		i++;
	}
	return (i);
}
