/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:46:18 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/29 17:13:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_ssl.h"

static int	unknown_opt(t_ssl_opts *opts)
{
	ft_dprintf(STDERR_FILENO, "usage: %s %s [-pqrt] [-s string] [files ...]\n"
		, opts->argv[0], opts->argv[1]);
	return (0);
}

static int	stdin_opt(t_ssl_opts *opts)
{
	char	digest[MAX_DIGEST_BYTES + 1];

	if (opts->file_hash_fn(digest, STDIN_FILENO))
		ft_printf("%s\n", digest);
	else
	{
		ft_dprintf(STDERR_FILENO, "%s: unable to read from stdin\n"
			, opts->argv[0]);
		return (0);
	}
	return (1);
}

static int	string_opt(t_ssl_opts *opts, const char *str)
{
	char	digest[MAX_DIGEST_BYTES + 1];

	if (optarg == NULL)
	{
		ft_dprintf(STDERR_FILENO, "%s: option requires an argument -- s\n"
			, opts->argv[0]);
		return (0);
	}
	opts->hash_fn(digest, (const uint8_t *)str, ft_strlen(str));
	print_string_digest(opts, str, digest);
	return (1);
}

static int	parse_files(t_ssl_opts *opts, int index)
{
	int		ret;
	int		fd;
	char	digest[MAX_DIGEST_BYTES + 1];

	ret = 1;
	while (index < opts->argc)
	{
		fd = open(opts->argv[index], O_RDONLY);
		if (fd == -1 && (ret = 0) == 0)
			ft_dprintf(STDERR_FILENO, "%s: %s: unable to open\n"
				, opts->argv[0], opts->argv[index]);
		else
		{
			if (opts->file_hash_fn(digest, fd))
				print_file_digest(opts, opts->argv[index], digest);
			else if ((ret = 0) == 0)
				ft_dprintf(STDERR_FILENO, "%s: %s: unable to read\n"
					, opts->argv[0], opts->argv[index]);
			close(fd);
		}
		index++;
	}
	return (ret);
}

int			parse_ssl_options(t_ssl_opts *opts)
{
	int	opt;

	optind = 2;
	while ((opt = getopt(opts->argc, opts->argv, "pqrs:")) != -1)
	{
		if (opt == 'q')
			opts->options |= OPT_QUIET;
		else if (opt == 'r')
			opts->options |= OPT_REVERSE;
		else if (opt == 'p')
			stdin_opt(opts);
		else if (opt == 's')
			string_opt(opts, optarg);
		else
			return (unknown_opt(opts));
	}
	parse_files(opts, optind);
	return (1);
}
