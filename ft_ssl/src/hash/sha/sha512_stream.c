/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_stream.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 09:50:29 by gguichar          #+#    #+#             */
/*   Updated: 2020/02/28 10:43:48 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "libft.h"
#include "hash_sha.h"
#include "hash_stream.h"
#include "utils.h"

void	sha384_stream_init(t_hash_stream *stream)
{
	static t_sha512_ctx	ctx;

	ft_memset(&ctx, 0, sizeof(t_sha512_ctx));
	ctx.hash.words[0] = 0xcbbb9d5dc1059ed8UL;
	ctx.hash.words[1] = 0x629a292a367cd507UL;
	ctx.hash.words[2] = 0x9159015a3070dd17UL;
	ctx.hash.words[3] = 0x152fecd8f70e5939UL;
	ctx.hash.words[4] = 0x67332667ffc00b31UL;
	ctx.hash.words[5] = 0x8eb44a8768581511UL;
	ctx.hash.words[6] = 0xdb0c2e0d64f98fa7UL;
	ctx.hash.words[7] = 0x47b5481dbefa4fa4UL;
	ctx.digest_size = SHA384_DIGEST_SIZE;
	stream->ctx = &ctx;
	stream->block = ctx.words;
	stream->block_size = SHA512_BLOCK_SIZE;
	stream->final_len_size = sizeof(uint64_t) * 2;
	stream->digest_buffer = ctx.digest;
	stream->hash_fn = (void *)sha512_stream;
	stream->final_fn = (void *)sha512_final;
	stream->digest_fn = (void *)sha512_digest;
}

void	sha512_stream_init(t_hash_stream *stream)
{
	static t_sha512_ctx	ctx;

	ft_memset(&ctx, 0, sizeof(t_sha512_ctx));
	ctx.hash.words[0] = 0x6a09e667f3bcc908UL;
	ctx.hash.words[1] = 0xbb67ae8584caa73bUL;
	ctx.hash.words[2] = 0x3c6ef372fe94f82bUL;
	ctx.hash.words[3] = 0xa54ff53a5f1d36f1UL;
	ctx.hash.words[4] = 0x510e527fade682d1UL;
	ctx.hash.words[5] = 0x9b05688c2b3e6c1fUL;
	ctx.hash.words[6] = 0x1f83d9abfb41bd6bUL;
	ctx.hash.words[7] = 0x5be0cd19137e2179UL;
	ctx.digest_size = SHA512_DIGEST_SIZE;
	stream->ctx = &ctx;
	stream->block = ctx.words;
	stream->block_size = SHA512_BLOCK_SIZE;
	stream->final_len_size = sizeof(uint64_t) * 2;
	stream->digest_buffer = ctx.digest;
	stream->hash_fn = (void *)sha512_stream;
	stream->final_fn = (void *)sha512_final;
	stream->digest_fn = (void *)sha512_digest;
}

void	sha512_final(t_sha512_ctx *ctx
	, uint64_t len_bits_hi, uint64_t len_bits_lo)
{
	len_bits_hi = byte_swap64(len_bits_hi);
	len_bits_lo = byte_swap64(len_bits_lo);
	ft_memcpy(ctx->words + 14, &len_bits_hi, sizeof(len_bits_hi));
	ft_memcpy(ctx->words + 15, &len_bits_lo, sizeof(len_bits_lo));
}
