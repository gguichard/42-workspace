/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha2.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 13:30:40 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/28 01:22:36 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_SHA2_H
# define FT_SSL_SHA2_H

# include <stdint.h>
# include <string.h>
# include "ft_ssl.h"

# define SHA2_HASH_CH(x, y, z) ((x & y) ^ (~x & z))
# define SHA2_HASH_MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
# define SHA2_HASH_BSIG0(x) ((UTILS_ROTATERIGHT(x, 2)) \
	^ (UTILS_ROTATERIGHT(x, 13)) ^ (UTILS_ROTATERIGHT(x, 22)))
# define SHA2_HASH_BSIG1(x) ((UTILS_ROTATERIGHT(x, 6)) \
	^ (UTILS_ROTATERIGHT(x, 11)) ^ (UTILS_ROTATERIGHT(x, 25)))
# define SHA2_HASH_SSIG0(x) ((UTILS_ROTATERIGHT(x, 7)) \
	^ (UTILS_ROTATERIGHT(x, 18)) ^ ((x) >> 3))
# define SHA2_HASH_SSIG1(x) ((UTILS_ROTATERIGHT(x, 17)) \
	^ (UTILS_ROTATERIGHT(x, 19)) ^ ((x) >> 10))

typedef struct	s_sha2_stream
{
	size_t		len;
	size_t		total_len;
	uint8_t		buffer[64];
	size_t		offset;
	void		(*hash_fn)(struct s_sha2_stream *
		, const uint8_t *, size_t, size_t);
	uint32_t	hash[8];
}				t_sha2_stream;

void	sha256_stream_fn(t_sha2_stream *stream
	, const uint8_t *bytes, size_t len, size_t offset);
void	sha256_process_words(uint32_t hash[8], uint32_t words[64]);

void	sha256_hash(const uint8_t *bytes, size_t len);
void	sha256_stream_file(int fd);
void	sha256_print_digest(uint32_t states[4]);

#endif
