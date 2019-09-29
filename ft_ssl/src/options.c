/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:35:44 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/29 15:06:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "options.h"
#include "ft_ssl.h"

static int	unknown_opt(t_ssl_opts *opts)
{
	ft_dprintf(STDERR_FILENO, "%s: illegal option -- %c\n"
		, opts->argv[0], opts->sub_opts.error);
	ft_dprintf(STDERR_FILENO, "usage: %s %s [-pqrt] [-s string] [files ...]\n"
		, opts->argv[0], opts->argv[1]);
	return (0);
}

static int	parse_string_opt(t_ssl_opts *opts)
{
	const char	*str;
	char		digest[MAX_DIGEST_BYTES + 1];

	str = ft_strchr(opts->argv[opts->index], 's') + 1;
	if (*str == '\0')
	{
		opts->index += 1;
		str = opts->argv[opts->index];
	}
	if (str == NULL)
	{
		ft_dprintf(STDERR_FILENO, "%s: option requires an argument -- s\n"
			, opts->argv[0]);
		return (0);
	}
	opts->hash_fn(digest, (const uint8_t *)str, ft_strlen(str));
	print_string_digest(opts, str, digest);
	return (1);
}

static int	parse_as_files(t_ssl_opts *opts)
{
	int		ret;
	int		fd;
	char	digest[MAX_DIGEST_BYTES + 1];

	ret = 1;
	while (opts->argv[opts->index] != NULL)
	{
		fd = open(opts->argv[opts->index], O_RDONLY);
		if (fd == -1 && (ret = 0) == 0)
			ft_dprintf(STDERR_FILENO, "%s: %s: unable to open\n"
				, opts->argv[0], opts->argv[opts->index]);
		else
		{
			if (opts->file_hash_fn(digest, fd))
				print_file_digest(opts, opts->argv[opts->index], digest);
			else if ((ret = 0) == 0)
				ft_dprintf(STDERR_FILENO, "%s: %s: unable to read\n"
					, opts->argv[0], opts->argv[opts->index]);
			close(fd);
		}
		opts->index += 1;
	}
	return (ret);
}

int			parse_ssl_options(t_ssl_opts *opts)
{
	while (opts->argv[opts->index] != NULL)
	{
		parse_opts(&opts->sub_opts, opts->argv + opts->index, "pqr");
		opts->sub_opts.value |= opts->prev_options;
		opts->index += opts->sub_opts.index;
		if (opts->sub_opts.error != '\0' && opts->sub_opts.error != 's')
			return (unknown_opt(opts));
		else if (opts->sub_opts.error == '\0')
			return (parse_as_files(opts));
		else if (!parse_string_opt(opts))
			return (0);
		opts->prev_options = opts->sub_opts.value;
	}
	return (1);
}