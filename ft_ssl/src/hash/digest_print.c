/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:36:44 by gguichar          #+#    #+#             */
/*   Updated: 2020/02/28 09:37:25 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "options.h"
#include "ft_ssl.h"

void	print_string_digest(t_ssl_opts *opts, t_cmd *cmd
	, const char *str, const char *digest)
{
	if (opts->options & HASH_OPT_QUIET)
		ft_printf("%s\n", digest);
	else if (opts->options & HASH_OPT_REVERSE)
		ft_printf("%s \"%s\"\n", digest, str);
	else
		ft_printf("%s (\"%s\") = %s\n", cmd->display, str, digest);
}

void	print_file_digest(t_ssl_opts *opts, t_cmd *cmd
	, const char *filename, const char *digest)
{
	if (opts->options & HASH_OPT_QUIET)
		ft_printf("%s\n", digest);
	else if (opts->options & HASH_OPT_REVERSE)
		ft_printf("%s %s\n", digest, filename);
	else
		ft_printf("%s (%s) = %s\n", cmd->display, filename, digest);
}
