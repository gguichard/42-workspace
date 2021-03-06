/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:41:11 by gguichar          #+#    #+#             */
/*   Updated: 2019/03/20 20:17:02 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "options.h"

static int	parse_cur_arg(t_opts *opts, char **argv)
{
	int	index;
	int	offset;

	index = 1;
	while (argv[opts->index][index] != '\0')
	{
		offset = find_opt_offset(opts->optstring, argv[opts->index][index]);
		if (offset < 0)
		{
			opts->error = argv[opts->index][index];
			return (0);
		}
		opts->value |= (1 << offset);
		if (*(ft_strchr(opts->optstring
						, argv[opts->index][index++]) + 1) == ':')
		{
			if (argv[opts->index][index] == '\0')
				(opts->args)[offset] = argv[++opts->index];
			else
				(opts->args)[offset] = &(argv[opts->index][index]);
			return (1);
		}
	}
	return (index != 1);
}

void		parse_opts(t_opts *opts, char **argv, const char *optstring)
{
	check_optstring(optstring);
	opts->value = 0;
	opts->index = 1;
	opts->error = 0;
	opts->optstring = optstring;
	while (argv[opts->index] != NULL)
	{
		if (ft_strequ(argv[opts->index], "--"))
		{
			(opts->index)++;
			break ;
		}
		if (argv[opts->index][0] != '-' || !parse_cur_arg(opts, argv))
			break ;
		(opts->index)++;
	}
}
