/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 13:30:40 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/15 17:27:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_SHA_H
# define FT_SSL_SHA_H

# include <stdint.h>
# include <string.h>
# include "hash_stream.h"
# include "utils.h"

# define RR UTILS_ROTATERIGHT

# define SHA1_BLOCK_SIZE 64
# define SHA256_BLOCK_SIZE 64
# define SHA512_BLOCK_SIZE 128

# define SHA224_DIGEST_SIZE 28
# define SHA256_DIGEST_SIZE 32
# define SHA384_DIGEST_SIZE 48
# define SHA512_DIGEST_SIZE 64

# define SHA1_HASH_1(b, c, d) ((b & c) | (~b & d))
# define SHA1_HASH_2(b, c, d) (b ^ c ^ d)
# define SHA1_HASH_3(b, c, d) ((b & c) | (b & d) | (c & d))
# define SHA1_HASH_4(b, c, d) (b ^ c ^ d)

# define SHA256_HASH_CH(x, y, z) ((x & y) ^ (~x & z))
# define SHA256_HASH_MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
# define SHA256_HASH_BSIG0(x) ((RR(x, 2)) ^ (RR(x, 13)) ^ (RR(x, 22)))
# define SHA256_HASH_BSIG1(x) ((RR(x, 6)) ^ (RR(x, 11)) ^ (RR(x, 25)))
# define SHA256_HASH_SSIG0(x) ((RR(x, 7)) ^ (RR(x, 18)) ^ ((x) >> 3))
# define SHA256_HASH_SSIG1(x) ((RR(x, 17)) ^ (RR(x, 19)) ^ ((x) >> 10))

# define SHA512_HASH_CH(x, y, z) ((x & y) ^ (~x & z))
# define SHA512_HASH_MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
# define SHA512_HASH_BSIG0(x) ((RR(x, 28)) ^ (RR(x, 34)) ^ (RR(x, 39)))
# define SHA512_HASH_BSIG1(x) ((RR(x, 14)) ^ (RR(x, 18)) ^ (RR(x, 41)))
# define SHA512_HASH_SSIG0(x) ((RR(x, 1)) ^ (RR(x, 8)) ^ ((x) >> 7))
# define SHA512_HASH_SSIG1(x) ((RR(x, 19)) ^ (RR(x, 61)) ^ ((x) >> 6))

union			u_sha1_hash
{
	uint32_t	words[5];
	uint8_t		bytes[20];
};

union			u_sha256_hash
{
	uint32_t	words[8];
	uint8_t		bytes[32];
};

union			u_sha512_hash
{
	uint64_t	words[8];
	uint8_t		bytes[64];
};

typedef struct	s_sha1_ctx
{
	char				digest[41];
	uint32_t			words[80];
	union u_sha1_hash	hash;
}				t_sha1_ctx;

typedef struct	s_sha256_ctx
{
	size_t				digest_size;
	char				digest[65];
	uint32_t			words[64];
	union u_sha256_hash	hash;
}				t_sha256_ctx;

typedef struct	s_sha512_ctx
{
	size_t				digest_size;
	char				digest[129];
	uint64_t			words[80];
	union u_sha512_hash	hash;
}				t_sha512_ctx;

void			sha1_stream_init(t_hash_stream *stream);
void			sha224_stream_init(t_hash_stream *stream);
void			sha256_stream_init(t_hash_stream *stream);
void			sha384_stream_init(t_hash_stream *stream);
void			sha512_stream_init(t_hash_stream *stream);

void			sha1_stream(t_sha1_ctx *ctx);
void			sha256_stream(t_sha256_ctx *ctx);
void			sha512_stream(t_sha512_ctx *ctx);

void			sha1_final(t_sha1_ctx *ctx
	, uint64_t len_bits_hi, uint64_t len_bits_lo);
void			sha256_final(t_sha256_ctx *ctx
	, uint64_t len_bits_hi, uint64_t len_bits_lo);
void			sha512_final(t_sha512_ctx *ctx
	, uint64_t len_bits_hi, uint64_t len_bits_lo);

void			sha1_digest(t_sha1_ctx *ctx);
void			sha256_digest(t_sha256_ctx *ctx);
void			sha512_digest(t_sha512_ctx *ctx);

#endif
