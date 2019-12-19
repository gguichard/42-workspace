/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 11:05:50 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/19 12:39:58 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "ft_ssl.h"
#include "ft_ssl_sha.h"
#include "utils.h"

#include UTILS_ROTATE_LEFT32
#include SHA1_HASH_FN

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
			value = sha1_hash_1(output[1], output[2], output[3]);
		else if (idx < 40)
			value = sha1_hash_2(output[1], output[2], output[3]);
		else if (idx < 60)
			value = sha1_hash_3(output[1], output[2], output[3]);
		else
			value = sha1_hash_4(output[1], output[2], output[3]);
		value += rotate_left32(output[0], 5) + output[4] + words[idx];
		value += g_sha1_hash[idx];
		output[4] = output[3];
		output[3] = output[2];
		output[2] = rotate_left32(output[1], 30);
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
		ctx->words[idx] = rotate_left32(ctx->words[idx - 3]
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
