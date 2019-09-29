/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:17:49 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/29 17:15:13 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdint.h>
# include <string.h>

# define MAX_DIGEST_BYTES 64

# define UTILS_MIN(x, y) (x > y ? y : x)
# define UTILS_ROTATELEFT(n, s) (((n) << s) | ((n) >> (sizeof(n) * 8 - s)))
# define UTILS_ROTATERIGHT(n, s) (((n) >> s) | ((n) << (sizeof(n) * 8 - s)))

# define OPT_QUIET (1 << 0)
# define OPT_REVERSE (1 << 1)

typedef struct	s_ssl_opts
{
	char		hash_name[8];
	int			options;
	int			argc;
	char		**argv;
	void		(*hash_fn)(char *, const uint8_t *, size_t);
	int			(*file_hash_fn)(char *, int);
}				t_ssl_opts;

typedef struct	s_hash_stream
{
	uint8_t		big_endian;
	size_t		len;
	uint8_t		buffer[64];
	size_t		offset;
	void		(*hash_fn)(uint32_t *, const uint8_t *);
	uint32_t	hash[0];
}				t_hash_stream;

void			hash_stream_begin(t_hash_stream *stream);
void			hash_stream_end(t_hash_stream *stream);
void			hash_stream(t_hash_stream *stream
	, const uint8_t *bytes, size_t len);

uint64_t		byte_swap64(uint64_t x);
void			digest_hex(char buffer[2], uint8_t byte);

void			print_string_digest(t_ssl_opts *opts, const char *str
	, char digest[65]);
void			print_file_digest(t_ssl_opts *opts, const char *filename
	, char digest[65]);
int				parse_ssl_options(t_ssl_opts *opts);

#endif
