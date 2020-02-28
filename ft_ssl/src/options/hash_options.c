/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:46:18 by gguichar          #+#    #+#             */
/*   Updated: 2020/02/28 09:49:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_ssl.h"
#include "hash_stream.h"

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
	return (1);
}

static int	stdin_opt(t_ssl_opts *opts, t_cmd *cmd, int in_out)
{
	char	*digest;

	opts->hash_count += 1;
	digest = hash_stream_file((t_hash_fn)cmd->fn, STDIN_FILENO, in_out);
	if (digest != NULL)
		ft_printf("%s\n", digest);
	else
	{
		ft_dprintf(STDERR_FILENO, "%s: unable to read from stdin\n"
			, opts->prefix);
		return (1);
	}
	return (0);
}

static int	string_opt(t_ssl_opts *opts, t_cmd *cmd, const char *optarg)
{
	char	*digest;

	opts->hash_count += 1;
	if (optarg == NULL)
		return (unknown_opt(opts, 's'));
	digest = hash_stream_bytes((t_hash_fn)cmd->fn, (const uint8_t *)optarg
			, ft_strlen(optarg));
	print_string_digest(opts, cmd, optarg, digest);
	return (0);
}

static int	parse_files(t_ssl_opts *opts, t_cmd *cmd, int index)
{
	int		ret;
	int		fd;
	char	*digest;

	ret = 0;
	while (index < opts->argc)
	{
		opts->hash_count += 1;
		fd = open(opts->argv[index], O_RDONLY);
		if (fd == -1 && (ret = 1) == 1)
			ft_dprintf(STDERR_FILENO, "%s: %s: unable to open file\n"
				, opts->prefix, opts->argv[index]);
		else
		{
			digest = hash_stream_file((t_hash_fn)cmd->fn, fd, 0);
			if (digest != NULL)
				print_file_digest(opts, cmd, opts->argv[index], digest);
			else if ((ret = 1) == 1)
				ft_dprintf(STDERR_FILENO, "%s: %s: unable to read file\n"
					, opts->prefix, opts->argv[index]);
			close(fd);
		}
		index++;
	}
	return (ret);
}

int			parse_hash_options(t_ssl_opts *opts, t_cmd *cmd)
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
			opts->options |= HASH_OPT_QUIET;
		else if (opt == 'r')
			opts->options |= HASH_OPT_REVERSE;
		else if (opt == 'p')
			ret |= stdin_opt(opts, cmd, 1);
		else if (opt == 's')
			ret |= string_opt(opts, cmd, getopt.optarg);
		else
			return (unknown_opt(opts, opt));
	}
	ret |= parse_files(opts, cmd, getopt.index);
	if (ret == 0 && opts->hash_count == 0)
		ret |= stdin_opt(opts, cmd, 0);
	return (ret);
}
