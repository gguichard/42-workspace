/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:18:10 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/30 23:01:35 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_ssl.h"
#include "ft_ssl_md5.h"
#include "ft_ssl_sha2.h"

static int	parse_command(t_ssl_opts *opts, const char *cmd)
{
	if (ft_strequ("md5", cmd))
	{
		opts->stream_init_fn = md5_stream_init;
		ft_strcpy(opts->hash_name, "MD5");
		return (1);
	}
	else if (ft_strequ("sha256", cmd))
	{
		opts->stream_init_fn = sha256_stream_init;
		ft_strcpy(opts->hash_name, "SHA256");
		return (1);
	}
	return (0);
}

static void	usage_help(char **argv)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: not a valid command\n\n"
		, argv[0], argv[1]);
	ft_dprintf(STDERR_FILENO, "Message digest commands:\nmd5\nsha256\n");
}

int			main(int argc, char **argv)
{
	t_ssl_opts	opts;

	if (argc < 2)
		ft_printf("usage: %s command [command opts] [command args]\n", argv[0]);
	else
	{
		ft_memset(&opts, 0, sizeof(t_ssl_opts));
		if (!parse_command(&opts, argv[1]))
			usage_help(argv);
		else
		{
			opts.argc = argc;
			opts.argv = argv;
			if (parse_ssl_options(&opts))
				return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
