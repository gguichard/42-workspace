/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 11:05:50 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/15 17:20:35 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "ft_ssl_sha.h"
#include "utils.h"

static const uint32_t	g_sha1_hash[80] = {
	0x5a827999, 0x5a827999, 0x5a827999, 0x5a827999,
	0x5a827999, 0x5a827999, 0x5a827999, 0x5a827999,
	0x5a827999, 0x5a827999, 0x5a827999, 0x5a827999,
	0x5a827999, 0x5a827999, 0x5a827999, 0x5a827999,
	0x5a827999, 0x5a827999, 0x5a827999, 0x5a827999,
	0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1,
	0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1,
	0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1,
	0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1,
	0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1,
	0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc,
	0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc,
	0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc,
	0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc,
	0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc,
	0xca62c1d6, 0xca62c1d6, 0xca62c1d6, 0xca62c1d6,
	0xca62c1d6, 0xca62c1d6, 0xca62c1d6, 0xca62c1d6,
	0xca62c1d6, 0xca62c1d6, 0xca62c1d6, 0xca62c1d6,
	0xca62c1d6, 0xca62c1d6, 0xca62c1d6, 0xca62c1d6,
	0xca62c1d6, 0xca62c1d6, 0xca62c1d6, 0xca62c1d6
};

static void	sha1_steps(uint32_t words[80], uint32_t output[5])
{
	size_t		idx;
	uint32_t	value;

	idx = 0;
	while (idx < 80)
	{
		if (idx < 20)
			value = SHA1_HASH_1(output[1], output[2], output[3]);
		else if (idx < 40)
			value = SHA1_HASH_2(output[1], output[2], output[3]);
		else if (idx < 60)
			value = SHA1_HASH_3(output[1], output[2], output[3]);
		else
			value = SHA1_HASH_4(output[1], output[2], output[3]);
		value += UTILS_ROTATELEFT(output[0], 5) + output[4] + words[idx];
		value += g_sha1_hash[idx];
		output[4] = output[3];
		output[3] = output[2];
		output[2] = UTILS_ROTATELEFT(output[1], 30);
		output[1] = output[0];
		output[0] = value;
		idx++;
	}
}

static void	sha1_words(t_sha1_ctx *ctx)
{
	size_t	idx;

	idx = 0;
	while (idx < 16)
	{
		ctx->words[idx] = byte_swap32(ctx->words[idx]);
		idx++;
	}
	while (idx < 80)
	{
		ctx->words[idx] = UTILS_ROTATELEFT(ctx->words[idx - 3]
				^ ctx->words[idx - 8]
				^ ctx->words[idx - 14]
				^ ctx->words[idx - 16], 1);
		idx++;
	}
}

void		sha1_stream(t_sha1_ctx *ctx)
{
	size_t		idx;
	uint32_t	values[5];

	sha1_words(ctx);
	idx = 0;
	while (idx < 5)
	{
		values[idx] = ctx->hash.words[idx];
		idx++;
	}
	sha1_steps(ctx->words, values);
	idx = 0;
	while (idx < 5)
	{
		ctx->hash.words[idx] += values[idx];
		idx++;
	}
}
