/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:17:49 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/24 00:00:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdint.h>
# include <string.h>

# define UTILS_MIN(x, y) (x > y ? y : x)
# define UTILS_ROTATELEFT(n, s) (((n) << s) | ((n) >> (sizeof(n) * 8 - s)))
# define UTILS_ROTATERIGHT(n, s) (((n) >> s) | ((n) << (sizeof(n) * 8 - s)))

# define OPT_QUIET (1 << 0)
# define OPT_REVERSE (1 << 1)

typedef struct	s_hash_stream
{
	void		*ctx;
	uint8_t		*ctx_buffer;
	size_t		block_size;
	size_t		final_len_size;
	char		*digest_buffer;
	void		(*hash_fn)(void *);
	void		(*final_fn)(void *, size_t);
	void		(*digest_fn)(void *);
	size_t		offset;
	size_t		len;
}				t_hash_stream;

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

void			hash_stream_begin(t_hash_stream *stream);
void			hash_stream_end(t_hash_stream *stream);
void			hash_stream(t_hash_stream *stream
	, const uint8_t *bytes, size_t len);

char			*hash_stream_bytes(void (*init_fn)(t_hash_stream *)
	, const uint8_t *bytes, size_t len);
char			*hash_stream_file(void (*init_fn)(t_hash_stream *)
	, int fd, int in_out);

uint32_t		byte_swap32(uint32_t x);
uint64_t		byte_swap64(uint64_t x);
void			digest_hex(char buffer[2], uint8_t byte);

void			print_string_digest(t_ssl_opts *opts
	, const char *str, const char *digest);
void			print_file_digest(t_ssl_opts *opts
	, const char *filename, const char *digest);

int				run_command(const char *prefix, int argc, char **argv);
int				parse_ssl_options(t_ssl_opts *opts);

int				interactive_mode(const char *prefix);

#endif
