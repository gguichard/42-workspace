/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_stream.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 01:17:01 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/24 09:44:30 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "libft.h"
#include "ft_ssl_sha.h"
#include "hash_stream.h"
#include "utils.h"

void	sha224_stream_init(t_hash_stream *stream)
{
	static t_sha256_ctx	ctx;

	ft_memset(&ctx, 0, sizeof(t_sha256_ctx));
	ctx.hash.words[0] = 0xc1059ed8;
	ctx.hash.words[1] = 0x367cd507;
	ctx.hash.words[2] = 0x3070dd17;
	ctx.hash.words[3] = 0xf70e5939;
	ctx.hash.words[4] = 0xffc00b31;
	ctx.hash.words[5] = 0x68581511;
	ctx.hash.words[6] = 0x64f98fa7;
	ctx.hash.words[7] = 0xbefa4fa4;
	ctx.digest_size = SHA224_DIGEST_SIZE;
	stream->ctx = &ctx;
	stream->ctx_buffer = (uint8_t *)ctx.words;
	stream->block_size = SHA256_BLOCK_SIZE;
	stream->final_len_size = sizeof(uint64_t);
	stream->digest_buffer = ctx.digest;
	stream->hash_fn = (void *)sha256_stream;
	stream->final_fn = (void *)sha256_final;
	stream->digest_fn = (void *)sha256_digest;
}

void	sha256_stream_init(t_hash_stream *stream)
{
	static t_sha256_ctx	ctx;

	ft_memset(&ctx, 0, sizeof(t_sha256_ctx));
	ctx.hash.words[0] = 0x6a09e667;
	ctx.hash.words[1] = 0xbb67ae85;
	ctx.hash.words[2] = 0x3c6ef372;
	ctx.hash.words[3] = 0xa54ff53a;
	ctx.hash.words[4] = 0x510e527f;
	ctx.hash.words[5] = 0x9b05688c;
	ctx.hash.words[6] = 0x1f83d9ab;
	ctx.hash.words[7] = 0x5be0cd19;
	ctx.digest_size = SHA256_DIGEST_SIZE;
	stream->ctx = &ctx;
	stream->ctx_buffer = (uint8_t *)ctx.words;
	stream->block_size = SHA256_BLOCK_SIZE;
	stream->final_len_size = sizeof(uint64_t);
	stream->digest_buffer = ctx.digest;
	stream->hash_fn = (void *)sha256_stream;
	stream->final_fn = (void *)sha256_final;
	stream->digest_fn = (void *)sha256_digest;
}

void	sha256_final(t_sha256_ctx *ctx, size_t offset)
{
	uint64_t	len_bits;

	len_bits = (ctx->len + offset) * 8;
	len_bits = byte_swap64(len_bits);
	ft_memcpy((uint8_t *)ctx->words + 56, &len_bits, sizeof(len_bits));
}
