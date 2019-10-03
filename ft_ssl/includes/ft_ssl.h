/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:17:49 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/03 18:53:03 by gguichar         ###   ########.fr       */
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

typedef struct	s_hash_stream
{
	uint8_t		big_endian;
	size_t		len;
	uint8_t		buffer[64];
	size_t		offset;
	uint32_t	hash[8];
	void		(*hash_fn)(uint32_t *, const uint8_t *);
	void		(*digest_fn)(char *, uint32_t *);
}				t_hash_stream;

typedef struct	s_ssl_opts
{
	const char	*prefix;
	int			options;
	int			argc;
	char		**argv;
	int			hash_count;
	char		hash_name[8];
	void		(*stream_fn)(t_hash_stream *);
}				t_ssl_opts;

typedef struct	s_ssl_hash_cmd
{
	const char	*hash_cmd;
	const char	*hash_name;
	void		(*stream_fn)(t_hash_stream *);
}				t_ssl_hash_cmd;

void			hash_stream_begin(t_hash_stream *stream);
void			hash_stream_end(t_hash_stream *stream);
void			hash_stream(t_hash_stream *stream
	, const uint8_t *bytes, size_t len);

void			hash_stream_bytes(void (*init_fn)(t_hash_stream *)
	, char digest[65], const uint8_t *bytes, size_t len);
int				hash_stream_file(void (*init_fn)(t_hash_stream *)
	, char digest[65], int fd, int in_out);

uint64_t		byte_swap64(uint64_t x);
void			digest_hex(char buffer[2], uint8_t byte);

void			print_string_digest(t_ssl_opts *opts, const char *str
	, char digest[65]);
void			print_file_digest(t_ssl_opts *opts, const char *filename
	, char digest[65]);

int				run_command(const char *prefix, int argc, char **argv);
int				parse_ssl_options(t_ssl_opts *opts);

int				interactive_mode(const char *prefix);

#endif
