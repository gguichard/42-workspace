/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_stream.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:50:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/15 17:32:33 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "libft.h"
#include "ft_ssl_md5.h"
#include "hash_stream.h"
#include "utils.h"

void	md5_stream_init(t_hash_stream *stream)
{
	static t_md5_ctx	ctx;

	ft_memset(&ctx, 0, sizeof(t_md5_ctx));
	ctx.hash.words[0] = 0x67452301;
	ctx.hash.words[1] = 0xefcdab89;
	ctx.hash.words[2] = 0x98badcfe;
	ctx.hash.words[3] = 0x10325476;
	stream->ctx = &ctx;
	stream->block = ctx.words;
	stream->block_size = sizeof(ctx.words);
	stream->final_len_size = sizeof(uint64_t);
	stream->digest_buffer = ctx.digest;
	stream->hash_fn = (void *)md5_stream;
	stream->final_fn = (void *)md5_final;
	stream->digest_fn = (void *)md5_digest;
}

void	md5_final(t_md5_ctx *ctx, uint64_t len_bits_hi, uint64_t len_bits_lo)
{
	size_t	len_bits;

	(void)len_bits_hi;
	len_bits = len_bits_lo;
	ft_memcpy((uint8_t *)ctx->words + 56, &len_bits, sizeof(len_bits));
}
