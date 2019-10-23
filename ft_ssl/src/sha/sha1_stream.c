/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1_stream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 11:09:02 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/24 00:01:22 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "libft.h"
#include "ft_ssl.h"
#include "ft_ssl_sha.h"

void	sha1_stream_init(t_hash_stream *stream)
{
	static t_sha1_ctx	ctx;

	ft_memset(&ctx, 0, sizeof(t_sha1_ctx));
	ctx.hash.words[0] = 0x67452301;
	ctx.hash.words[1] = 0xEFCDAB89;
	ctx.hash.words[2] = 0x98BADCFE;
	ctx.hash.words[3] = 0x10325476;
	ctx.hash.words[4] = 0xC3D2E1F0;
	stream->ctx = &ctx;
	stream->ctx_buffer = (uint8_t *)ctx.words;
	stream->block_size = SHA1_BLOCK_SIZE;
	stream->digest_buffer = ctx.digest;
	stream->hash_fn = (void *)sha1_stream;
	stream->final_fn = (void *)sha1_final;
	stream->digest_fn = (void *)sha1_digest;
}

void	sha1_final(t_sha1_ctx *ctx, size_t offset)
{
	uint64_t	len_bits;

	len_bits = (ctx->len + offset) * 8;
	len_bits = byte_swap64(len_bits);
	ft_memcpy((uint8_t *)ctx->words + 56, &len_bits, sizeof(len_bits));
}
