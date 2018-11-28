/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 09:12:29 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/27 22:35:15 by gguichar         ###   ########.fr       */
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

static void	parse_override_opt(t_opt *opt, long new, long old)
{
	opt->options |= new;
	opt->options &= ~old;
}

static void	parse_opt(t_opt *opt, char c)
{
	if (c == 'C')
		parse_override_opt(opt, COL_OPT, ONE_OPT | LST_OPT);
	else if (c == '1')
		parse_override_opt(opt, ONE_OPT, COL_OPT | LST_OPT);
	else if (c == 'l')
		parse_override_opt(opt, LST_OPT, ONE_OPT | COL_OPT);
	else
		opt->options |= opt_mask(c);
}

void		parse_options(t_opt *opt, int argc, char **argv)
{
	int	index;

	opt->offset = 1;
	opt->options = 0;
	while (opt->offset < argc
			&& argv[opt->offset][0] == '-'
			&& argv[opt->offset][1] != '\0')
	{
		if (ft_strequ(argv[opt->offset], "--"))
		{
			(opt->offset)++;
			break ;
		}
		index = 1;
		while (argv[opt->offset][index] != '\0')
		{
			if (!ft_strchr(VALID_OPTIONS, argv[opt->offset][index]))
				invalid_opt(argv[opt->offset][index]);
			parse_opt(opt, argv[opt->offset][index]);
			index++;
		}
		(opt->offset)++;
	}
}
