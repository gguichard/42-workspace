/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 09:12:29 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/23 13:35:02 by gguichar         ###   ########.fr       */
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

static void	check_winsize(t_opt *opt)
{
	if (ioctl(0, TIOCGWINSZ, &(opt->ws)) != -1)
		opt->options |= COLUMN_OPT;
}

static void	parse_files(t_opt *opt, int argc, char **argv, int offset)
{
	int	files;
	int	i;

	files = argc - offset;
	if (files <= 0)
		opt->files = NULL;
	else
	{
		if (!(opt->files = (char **)malloc((files + 1) * sizeof(char *))))
			malloc_error();
		(opt->files)[files] = NULL;
		i = 0;
		while (i + offset < argc)
		{
			(opt->files)[i] = argv[i + offset];
			i++;
		}
	}
}

void		parse_options(t_opt *opt, int argc, char **argv)
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
			opt->options |= opt_mask(argv[i][j]);
			j++;
		}
		i++;
	}
	parse_files(opt, argc, argv, i);
	if (!(opt->options & opt_mask('l')))
		check_winsize(opt);
}
