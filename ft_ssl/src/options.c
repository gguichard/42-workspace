/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:46:18 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/02 19:02:31 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_ssl.h"

static int	unknown_opt(t_ssl_opts *opts, char opt)
{
	if (opt == 's')
		ft_dprintf(STDERR_FILENO, "%s: option requires an argument -- s\n"
			, opts->prefix);
	else
		ft_dprintf(STDERR_FILENO, "%s: illegal option -- %c\n"
			, opts->prefix, opt);
	ft_dprintf(STDERR_FILENO, "usage: %s %s [-pqr] [-s string] [files ...]\n"
		, opts->prefix, opts->argv[0]);
	return (0);
}

static int	stdin_opt(t_ssl_opts *opts, int in_out)
{
	char	digest[MAX_DIGEST_BYTES + 1];

	opts->hash_count += 1;
	if (hash_stream_file(opts->stream_init_fn, digest, STDIN_FILENO, in_out))
		ft_printf("%s\n", digest);
	else
	{
		ft_dprintf(STDERR_FILENO, "%s: unable to read from stdin\n"
			, opts->prefix);
		return (0);
	}
	return (1);
}

static int	string_opt(t_ssl_opts *opts, const char *optarg)
{
	char	digest[MAX_DIGEST_BYTES + 1];

	opts->hash_count += 1;
	if (optarg == NULL)
		return (unknown_opt(opts, 's'));
	hash_stream_bytes(opts->stream_init_fn, digest
		, (const uint8_t *)optarg, ft_strlen(optarg));
	print_string_digest(opts, optarg, digest);
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
		opts->hash_count += 1;
		fd = open(opts->argv[index], O_RDONLY);
		if (fd == -1 && (ret = 0) == 0)
			ft_dprintf(STDERR_FILENO, "%s: %s: unable to open file\n"
				, opts->prefix, opts->argv[index]);
		else
		{
			if (hash_stream_file(opts->stream_init_fn, digest, fd, 0))
				print_file_digest(opts, opts->argv[index], digest);
			else if ((ret = 0) == 0)
				ft_dprintf(STDERR_FILENO, "%s: %s: unable to read file\n"
					, opts->prefix, opts->argv[index]);
			close(fd);
		}
		index++;
	}
	return (ret);
}

int			parse_ssl_options(t_ssl_opts *opts)
{
	int			ret;
	t_getopt	getopt;
	int			opt;

	ret = 0;
	getopt.index = 1;
	getopt.offset = 0;
	while ((opt = ft_getopt(opts->argc, opts->argv, "pqrs:", &getopt)) != -1)
	{
		if (opt == 'q')
			opts->options |= OPT_QUIET;
		else if (opt == 'r')
			opts->options |= OPT_REVERSE;
		else if (opt == 'p')
			ret |= (!stdin_opt(opts, 1));
		else if (opt == 's')
			ret |= (!string_opt(opts, getopt.optarg));
		else
			return (unknown_opt(opts, opt));
	}
	ret |= (!parse_files(opts, getopt.index));
	if (ret == 0 && opts->hash_count == 0)
		ret |= (!stdin_opt(opts, 0));
	return (!ret);
}
