/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1_stream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 11:09:02 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/15 17:25:41 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "libft.h"
#include "ft_ssl_sha.h"
#include "hash_stream.h"
#include "utils.h"

void	sha1_stream_init(t_hash_stream *stream)
{
	static t_sha1_ctx	ctx;

	ft_memset(&ctx, 0, sizeof(t_sha1_ctx));
	ctx.hash.words[0] = 0x67452301;
	ctx.hash.words[1] = 0xefcdab89;
	ctx.hash.words[2] = 0x98badcfe;
	ctx.hash.words[3] = 0x10325476;
	ctx.hash.words[4] = 0xc3d2e1f0;
	stream->ctx = &ctx;
	stream->block = ctx.words;
	stream->block_size = SHA1_BLOCK_SIZE;
	stream->final_len_size = sizeof(uint64_t);
	stream->digest_buffer = ctx.digest;
	stream->hash_fn = (void *)sha1_stream;
	stream->final_fn = (void *)sha1_final;
	stream->digest_fn = (void *)sha1_digest;
}

void	sha1_final(t_sha1_ctx *ctx, uint64_t len_bits_hi, uint64_t len_bits_lo)
{
	uint64_t	len_bits;

	(void)len_bits_hi;
	len_bits = byte_swap64(len_bits_lo);
	ft_memcpy((uint8_t *)ctx->words + 56, &len_bits, sizeof(len_bits));
}
