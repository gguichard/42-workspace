/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:18:10 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/24 10:49:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_ssl.h"
#include "ft_ssl_md5.h"
#include "ft_ssl_sha.h"

static t_hash	g_hash_cmds[] = {
	{"md5", "MD5", md5_stream_init},
	{"sha1", "SHA-1", sha1_stream_init},
	{"sha224", "SHA-224", sha224_stream_init},
	{"sha256", "SHA-256", sha256_stream_init},
	{"sha384", "SHA-384", sha384_stream_init},
	{"sha512", "SHA-512", sha512_stream_init}
};

static void	usage_help(const char *prefix, const char *cmd)
{
	size_t	idx;

	ft_dprintf(STDERR_FILENO, "%s: %s: not a valid command\n", prefix, cmd);
	ft_dprintf(STDERR_FILENO, "\nStandard commands\nNone\n");
	ft_dprintf(STDERR_FILENO, "\nMessage Digest commands\n");
	idx = 0;
	while (idx < (sizeof(g_hash_cmds) / sizeof(g_hash_cmds[0])))
	{
		ft_dprintf(STDERR_FILENO, "%s\n", g_hash_cmds[idx].hash_cmd);
		idx++;
	}
	ft_dprintf(STDERR_FILENO, "\nCipher commands\nNone\n\n");
}

static int	setup_command(t_ssl_opts *opts, const char *cmd)
{
	size_t	idx;

	idx = 0;
	while (idx < (sizeof(g_hash_cmds) / sizeof(g_hash_cmds[0])))
	{
		if (ft_strequ(g_hash_cmds[idx].hash_cmd, cmd))
		{
			opts->hash = &g_hash_cmds[idx];
			return (1);
		}
		idx++;
	}
	return (0);
}

int			run_command(const char *prefix, int argc, char **argv)
{
	int			valid;
	t_ssl_opts	opts;

	valid = 0;
	ft_memset(&opts, 0, sizeof(t_ssl_opts));
	opts.prefix = prefix;
	if (!setup_command(&opts, argv[0]))
		usage_help(prefix, argv[0]);
	else
	{
		opts.argc = argc;
		opts.argv = argv;
		valid = parse_options(&opts);
	}
	return (valid);
}

int			main(int argc, char **argv)
{
	int	valid;

	if (argc < 2)
		valid = interactive_mode(argv[0]);
	else
		valid = run_command(argv[0], argc - 1, argv + 1);
	return (!valid ? EXIT_FAILURE : EXIT_SUCCESS);
}
