/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:17:49 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/17 12:05:35 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "hash_stream.h"

# define OPT_QUIET 0x1
# define OPT_REVERSE 0x2

typedef struct	s_hash
{
	const char	*hash_cmd;
	const char	*hash_name;
	void		(*stream_fn)(t_hash_stream *);
}				t_hash;

typedef struct	s_ssl_opts
{
	const char	*prefix;
	int			options;
	int			argc;
	char		**argv;
	t_hash		*hash;
	int			hash_count;
}				t_ssl_opts;

void			print_string_digest(t_ssl_opts *opts
	, const char *str, const char *digest);
void			print_file_digest(t_ssl_opts *opts
	, const char *filename, const char *digest);

int				run_command(const char *prefix, int argc, char **argv);
int				parse_options(t_ssl_opts *opts);

int				interactive_mode(const char *prefix);

#endif
