/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:36:44 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/29 16:58:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "options.h"
#include "ft_ssl.h"

void	print_string_digest(t_ssl_opts *opts, const char *str
	, char digest[65])
{
	if (opts->options & OPT_QUIET)
		ft_printf("%s\n", digest);
	else if (opts->options & OPT_REVERSE)
		ft_printf("%s \"%s\"\n", digest, str);
	else
		ft_printf("%s (\"%s\") = %s\n", opts->hash_name, str, digest);
}

void	print_file_digest(t_ssl_opts *opts, const char *filename
	, char digest[65])
{
	if (opts->options & OPT_QUIET)
		ft_printf("%s\n", digest);
	else if (opts->options & OPT_REVERSE)
		ft_printf("%s %s\n", digest, filename);
	else
		ft_printf("%s (%s) = %s\n", opts->hash_name, filename, digest);
}
