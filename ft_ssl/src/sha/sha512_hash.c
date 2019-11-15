/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 09:57:43 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/15 17:21:05 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "ft_ssl_sha.h"
#include "utils.h"

static const uint64_t	g_sha512_hash[80] = {
	0x428a2f98d728ae22UL, 0x7137449123ef65cdUL,
	0xb5c0fbcfec4d3b2fUL, 0xe9b5dba58189dbbcUL,
	0x3956c25bf348b538UL, 0x59f111f1b605d019UL,
	0x923f82a4af194f9bUL, 0xab1c5ed5da6d8118UL,
	0xd807aa98a3030242UL, 0x12835b0145706fbeUL,
	0x243185be4ee4b28cUL, 0x550c7dc3d5ffb4e2UL,
	0x72be5d74f27b896fUL, 0x80deb1fe3b1696b1UL,
	0x9bdc06a725c71235UL, 0xc19bf174cf692694UL,
	0xe49b69c19ef14ad2UL, 0xefbe4786384f25e3UL,
	0x0fc19dc68b8cd5b5UL, 0x240ca1cc77ac9c65UL,
	0x2de92c6f592b0275UL, 0x4a7484aa6ea6e483UL,
	0x5cb0a9dcbd41fbd4UL, 0x76f988da831153b5UL,
	0x983e5152ee66dfabUL, 0xa831c66d2db43210UL,
	0xb00327c898fb213fUL, 0xbf597fc7beef0ee4UL,
	0xc6e00bf33da88fc2UL, 0xd5a79147930aa725UL,
	0x06ca6351e003826fUL, 0x142929670a0e6e70UL,
	0x27b70a8546d22ffcUL, 0x2e1b21385c26c926UL,
	0x4d2c6dfc5ac42aedUL, 0x53380d139d95b3dfUL,
	0x650a73548baf63deUL, 0x766a0abb3c77b2a8UL,
	0x81c2c92e47edaee6UL, 0x92722c851482353bUL,
	0xa2bfe8a14cf10364UL, 0xa81a664bbc423001UL,
	0xc24b8b70d0f89791UL, 0xc76c51a30654be30UL,
	0xd192e819d6ef5218UL, 0xd69906245565a910UL,
	0xf40e35855771202aUL, 0x106aa07032bbd1b8UL,
	0x19a4c116b8d2d0c8UL, 0x1e376c085141ab53UL,
	0x2748774cdf8eeb99UL, 0x34b0bcb5e19b48a8UL,
	0x391c0cb3c5c95a63UL, 0x4ed8aa4ae3418acbUL,
	0x5b9cca4f7763e373UL, 0x682e6ff3d6b2b8a3UL,
	0x748f82ee5defb2fcUL, 0x78a5636f43172f60UL,
	0x84c87814a1f0ab72UL, 0x8cc702081a6439ecUL,
	0x90befffa23631e28UL, 0xa4506cebde82bde9UL,
	0xbef9a3f7b2c67915UL, 0xc67178f2e372532bUL,
	0xca273eceea26619cUL, 0xd186b8c721c0c207UL,
	0xeada7dd6cde0eb1eUL, 0xf57d4f7fee6ed178UL,
	0x06f067aa72176fbaUL, 0x0a637dc5a2c898a6UL,
	0x113f9804bef90daeUL, 0x1b710b35131c471bUL,
	0x28db77f523047d84UL, 0x32caab7b40c72493UL,
	0x3c9ebe0a15c9bebcUL, 0x431d67c49c100d4cUL,
	0x4cc5d4becb3e42b6UL, 0x597f299cfc657e2aUL,
	0x5fcb6fab3ad6faecUL, 0x6c44198c4a475817UL
};

static void	sha512_steps(uint64_t words[80], uint64_t output[8])
{
	size_t		idx;
	uint64_t	value1;
	uint64_t	value2;

	idx = 0;
	while (idx < 80)
	{
		value1 = output[7] + SHA512_HASH_BSIG1(output[4])
			+ SHA512_HASH_CH(output[4], output[5], output[6])
			+ g_sha512_hash[idx]
			+ words[idx];
		value2 = SHA512_HASH_BSIG0(output[0])
			+ SHA512_HASH_MAJ(output[0], output[1], output[2]);
		output[7] = output[6];
		output[6] = output[5];
		output[5] = output[4];
		output[4] = output[3] + value1;
		output[3] = output[2];
		output[2] = output[1];
		output[1] = output[0];
		output[0] = value1 + value2;
		idx++;
	}
}

static void	sha512_words(t_sha512_ctx *ctx)
{
	size_t	idx;

	idx = 0;
	while (idx < 16)
	{
		ctx->words[idx] = byte_swap64(ctx->words[idx]);
		idx++;
	}
	while (idx < 80)
	{
		ctx->words[idx] = SHA512_HASH_SSIG1(ctx->words[idx - 2])
			+ ctx->words[idx - 7]
			+ SHA512_HASH_SSIG0(ctx->words[idx - 15])
			+ ctx->words[idx - 16];
		idx++;
	}
}

void		sha512_stream(t_sha512_ctx *ctx)
{
	size_t		idx;
	uint64_t	values[8];

	sha512_words(ctx);
	idx = 0;
	while (idx < 8)
	{
		values[idx] = ctx->hash.words[idx];
		idx++;
	}
	sha512_steps(ctx->words, values);
	idx = 0;
	while (idx < 8)
	{
		ctx->hash.words[idx] += values[idx];
		idx++;
	}
}
