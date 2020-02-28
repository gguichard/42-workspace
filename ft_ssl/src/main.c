/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:18:10 by gguichar          #+#    #+#             */
/*   Updated: 2020/02/28 10:40:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_ssl.h"
#include "hash_md5.h"
#include "hash_sha.h"

static t_cmd	g_cmds[] = {
	{"md5", "MD5", HASH_CMD, md5_stream_init},
	{"sha1", "SHA-1", HASH_CMD, sha1_stream_init},
	{"sha224", "SHA-224", HASH_CMD, sha224_stream_init},
	{"sha256", "SHA-256", HASH_CMD, sha256_stream_init},
	{"sha384", "SHA-384", HASH_CMD, sha384_stream_init},
	{"sha512", "SHA-512", HASH_CMD, sha512_stream_init},
	{"base64", "Base64", CIPHER_CMD, NULL}
};

static void		filter_print_cmd(t_cmd_type filter_type)
{
	size_t	idx;

	idx = 0;
	while (idx < (sizeof(g_cmds) / sizeof(g_cmds[0])))
	{
		if (g_cmds[idx].type == filter_type)
			ft_dprintf(STDERR_FILENO, "%s\n", g_cmds[idx].id);
		idx++;
	}
}

static void		usage_help(const char *prefix, const char *cmd)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: not a valid command\n", prefix, cmd);
	ft_dprintf(STDERR_FILENO, "\nStandard commands\nNone\n");
	ft_dprintf(STDERR_FILENO, "\nMessage Digest commands\n");
	filter_print_cmd(HASH_CMD);
	ft_dprintf(STDERR_FILENO, "\nCipher commands\n");
	filter_print_cmd(CIPHER_CMD);
	ft_dprintf(STDERR_FILENO, "\n");
}

static t_cmd	*find_command(const char *cmd_id)
{
	size_t	idx;

	idx = 0;
	while (idx < (sizeof(g_cmds) / sizeof(g_cmds[0])))
	{
		if (ft_strequ(g_cmds[idx].id, cmd_id))
			return (&g_cmds[idx]);
		idx++;
	}
	return (0);
}

int				exec_command(const char *prefix, int argc, char **argv)
{
	int			ret;
	t_ssl_opts	opts;
	t_cmd		*cmd;

	ret = 1;
	ft_memset(&opts, 0, sizeof(t_ssl_opts));
	opts.prefix = prefix;
	cmd = find_command(argv[0]);
	if (cmd == NULL)
		usage_help(prefix, argv[0]);
	else
	{
		opts.argc = argc;
		opts.argv = argv;
		if (cmd->type == HASH_CMD)
			ret = parse_hash_options(&opts, cmd);
	}
	return (ret);
}

int				main(int argc, char **argv)
{
	const char	*prefix;
	int			ret;

	prefix = argv[0];
	if (argc >= 2)
		ret = exec_command(prefix, argc - 1, argv + 1);
	else
	{
		ft_printf("No argument supplied, falling back to interactive mode.\n");
		ret = interactive_mode(prefix);
	}
	return (ret ? EXIT_FAILURE : EXIT_SUCCESS);
}
