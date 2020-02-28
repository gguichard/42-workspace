/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:17:49 by gguichar          #+#    #+#             */
/*   Updated: 2020/02/28 09:41:42 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "hash_stream.h"
# include "cipher_stream.h"

# define HASH_OPT_QUIET 0x1
# define HASH_OPT_REVERSE 0x2

typedef void	(*t_hash_fn)(t_hash_stream *hash_stream);
typedef void	(*t_cipher_fn)(t_cipher_stream *cipher_stream);

typedef enum	e_cmd_type
{
	HASH_CMD,
	CIPHER_CMD,
}				t_cmd_type;

typedef struct	s_cmd
{
	const char	*id;
	const char	*display;
	t_cmd_type	type;
	void		*fn;
}				t_cmd;

typedef struct	s_ssl_opts
{
	const char	*prefix;
	int			options;
	int			argc;
	char		**argv;
	int			hash_count;
}				t_ssl_opts;

void			print_string_digest(t_ssl_opts *opts, t_cmd *cmd
	, const char *str, const char *digest);
void			print_file_digest(t_ssl_opts *opts, t_cmd *cmd
	, const char *filename, const char *digest);

int				exec_command(const char *prefix, int argc, char **argv);
int				parse_hash_options(t_ssl_opts *opts, t_cmd *cmd);

int				interactive_mode(const char *prefix);

#endif
