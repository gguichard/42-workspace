/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_stream.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 01:17:01 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/30 22:57:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "ft_ssl.h"
#include "ft_ssl_sha2.h"

static void	sha256_stream(uint32_t hash[8], const uint8_t *bytes)
{
	size_t		idx;
	uint32_t	buffer[64];

	idx = 0;
	while (idx < 16)
	{
		buffer[idx] = (bytes[idx * 4] << 24)
			| (bytes[idx * 4 + 1] << 16)
			| (bytes[idx * 4 + 2] << 8)
			| bytes[idx * 4 + 3];
		idx++;
	}
	while (idx < 64)
	{
		buffer[idx] = SHA2_HASH_SSIG1(buffer[idx - 2]) + buffer[idx - 7]
			+ SHA2_HASH_SSIG0(buffer[idx - 15]) + buffer[idx - 16];
		idx++;
	}
	sha256_roll(hash, buffer);
}

void		sha256_stream_init(t_hash_stream *stream)
{
	stream->big_endian = 1;
	stream->hash[0] = 0x6a09e667;
	stream->hash[1] = 0xbb67ae85;
	stream->hash[2] = 0x3c6ef372;
	stream->hash[3] = 0xa54ff53a;
	stream->hash[4] = 0x510e527f;
	stream->hash[5] = 0x9b05688c;
	stream->hash[6] = 0x1f83d9ab;
	stream->hash[7] = 0x5be0cd19;
	stream->hash_fn = sha256_stream;
	stream->digest_fn = sha256_digest;
}
