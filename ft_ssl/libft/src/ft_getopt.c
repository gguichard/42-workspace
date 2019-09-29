/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:52:01 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/29 19:56:31 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	getopt_nextarg(t_getopt *opt)
{
	opt->index += 1;
	opt->offset = 0;
}

static int	getopt_arg(char **argv, const char *optstring, t_getopt *opt)
{
	char	*tmp_opt;

	tmp_opt = ft_strchr(optstring, argv[opt->index][opt->offset]);
	if (tmp_opt == NULL)
		return (argv[opt->index][opt->offset]);
	else if (*(tmp_opt + 1) != ':')
	{
		opt->offset += 1;
		if (argv[opt->index][opt->offset] == '\0')
			getopt_nextarg(opt);
	}
	else
	{
		opt->optarg = NULL;
		if (argv[opt->index][opt->offset + 1] != '\0')
			opt->optarg = &argv[opt->index][opt->offset + 1];
		else
		{
			opt->index += 1;
			opt->optarg = argv[opt->index];
		}
		getopt_nextarg(opt);
	}
	return (*tmp_opt);
}

int			ft_getopt(int argc, char **argv, const char *optstring
	, t_getopt *opt)
{
	if (opt->index >= argc)
		return (-1);
	else if (opt->offset == 0)
	{
		if (argv[opt->index][0] != '-' || argv[opt->index][1] == '\0')
			return (-1);
		else if (ft_strequ(argv[opt->index], "--"))
		{
			opt->index += 1;
			return (-1);
		}
		opt->offset += 1;
	}
	return (getopt_arg(argv, optstring, opt));
}
