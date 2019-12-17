/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 13:30:40 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/17 12:24:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_SHA_H
# define FT_SSL_SHA_H

# include <stdint.h>
# include <string.h>
# include "hash_stream.h"
# include "utils.h"

# define SHA1_BLOCK_SIZE 64
# define SHA256_BLOCK_SIZE 64
# define SHA512_BLOCK_SIZE 128

# define SHA224_DIGEST_SIZE 28
# define SHA256_DIGEST_SIZE 32
# define SHA384_DIGEST_SIZE 48
# define SHA512_DIGEST_SIZE 64

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

uint32_t		sha1_hash_1(uint32_t b, uint32_t c, uint32_t d);
uint32_t		sha1_hash_2(uint32_t b, uint32_t c, uint32_t d);
uint32_t		sha1_hash_3(uint32_t b, uint32_t c, uint32_t d);
uint32_t		sha1_hash_4(uint32_t b, uint32_t c, uint32_t d);

uint32_t		sha256_hash_ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t		sha256_hash_maj(uint32_t x, uint32_t y, uint32_t z);
uint32_t		sha256_hash_bsig0(uint32_t x);
uint32_t		sha256_hash_bsig1(uint32_t x);
uint32_t		sha256_hash_ssig0(uint32_t x);
uint32_t		sha256_hash_ssig1(uint32_t x);

uint64_t		sha512_hash_ch(uint64_t x, uint64_t y, uint64_t z);
uint64_t		sha512_hash_maj(uint64_t x, uint64_t y, uint64_t z);
uint64_t		sha512_hash_bsig0(uint64_t x);
uint64_t		sha512_hash_bsig1(uint64_t x);
uint64_t		sha512_hash_ssig0(uint64_t x);
uint64_t		sha512_hash_ssig1(uint64_t x);

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
