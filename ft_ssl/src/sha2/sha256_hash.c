/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 13:25:34 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/28 18:52:13 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "ft_ssl.h"
#include "ft_ssl_sha2.h"

static const uint32_t	g_sha2_hash[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void	sha256_steps(uint32_t words[64], uint32_t output[8])
{
	size_t		idx;
	uint32_t	value1;
	uint32_t	value2;

	idx = 0;
	while (idx < 64)
	{
		value1 = output[7] + SHA2_HASH_BSIG1(output[4])
			+ SHA2_HASH_CH(output[4], output[5], output[6])
			+ g_sha2_hash[idx] + words[idx];
		value2 = SHA2_HASH_BSIG0(output[0])
			+ SHA2_HASH_MAJ(output[0], output[1], output[2]);
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

void		sha256_roll(uint32_t hash[8], uint32_t words[64])
{
	size_t		idx;
	uint32_t	values[8];

	idx = 0;
	while (idx < 8)
	{
		values[idx] = hash[idx];
		idx++;
	}
	sha256_steps(words, values);
	idx = 0;
	while (idx < 8)
	{
		hash[idx] += values[idx];
		idx++;
	}
}

void		sha256_hash(const uint8_t *bytes, size_t len)
{
	t_sha2_stream	stream;

	sha256_stream_init(&stream);
	hash_stream_begin((t_hash_stream *)&stream);
	hash_stream((t_hash_stream *)&stream, bytes, len);
	hash_stream_end((t_hash_stream *)&stream);
	sha256_print_digest(stream.hash);
}
