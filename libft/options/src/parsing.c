/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:41:11 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/20 21:42:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "options.h"

static int	parse_cur_arg(t_opt *opt, char **argv)
{
	int	index;
	int	offset;

	index = 1;
	while (argv[opt->index][index] != '\0')
	{
		offset = find_opt_offset(opt->optstring, argv[opt->index][index]);
		if (offset < 0)
		{
			opt->error = argv[opt->index][index];
			return (0);
		}
		opt->value |= (1 << offset);
		if (*(ft_strchr(opt->optstring, argv[opt->index][index++]) + 1) == ':')
		{
			if (argv[opt->index][index] == '\0')
				(opt->args)[offset] = argv[++opt->index];
			else
				(opt->args)[offset] = &(argv[opt->index][index]);
			return (1);
		}
	}
	return (index != 1);
}

t_opt		*parse_opts(int argc, char **argv, const char *optstring)
{
	static t_opt	opt;

	check_optstring(optstring);
	opt.value = 0;
	opt.index = 1;
	opt.error = 0;
	opt.optstring = optstring;
	while (opt.index < argc)
	{
		if (ft_strequ(argv[opt.index], "--"))
		{
			(opt.index)++;
			break ;
		}
		if (argv[opt.index][0] != '-' || !parse_cur_arg(&opt, argv))
			break ;
		(opt.index)++;
	}
	return (&opt);
}
