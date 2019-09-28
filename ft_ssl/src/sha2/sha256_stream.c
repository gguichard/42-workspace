/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_stream.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 01:17:01 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/28 16:50:58 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "ft_ssl.h"
#include "ft_ssl_sha2.h"

static uint8_t	sha256_byte(const uint8_t *bytes, size_t len, size_t index)
{
	if (index < len)
		return (bytes[index]);
	else if (index == len)
		return (1 << 7);
	else
		return (0);
}

static void		sha256_roll_words(uint32_t words[64])
{
	size_t	idx;

	idx = 16;
	while (idx < 64)
	{
		words[idx] = SHA2_HASH_SSIG1(words[idx - 2]) + words[idx - 7]
			+ SHA2_HASH_SSIG0(words[idx - 15]) + words[idx - 16];
		idx++;
	}
}

static void		sha256_stream_fn(t_sha2_stream *stream
	, const uint8_t *bytes, size_t len, size_t offset)
{
	size_t		idx;
	uint32_t	buffer[64];

	idx = 0;
	while (idx < 16)
	{
		if (offset <= len)
			buffer[idx] = ((uint32_t)sha256_byte(bytes, len, offset) << 24)
					| ((uint32_t)sha256_byte(bytes, len, offset + 1) << 16)
					| ((uint32_t)sha256_byte(bytes, len, offset + 2) << 8)
					| (uint32_t)sha256_byte(bytes, len, offset + 3);
		else if ((offset + 4) == stream->total_len)
			buffer[idx] = (len * 8) & 0xffffffff;
		else if ((offset + 8) == stream->total_len)
			buffer[idx] = (len * 8) >> 32;
		else
			buffer[idx] = 0;
		offset += 4;
		idx++;
	}
	sha256_roll_words(buffer);
	sha256_process_words(stream->hash, buffer);
}

void			sha256_stream_init(t_sha2_stream *stream)
{
	stream->hash[0] = 0x6a09e667;
	stream->hash[1] = 0xbb67ae85;
	stream->hash[2] = 0x3c6ef372;
	stream->hash[3] = 0xa54ff53a;
	stream->hash[4] = 0x510e527f;
	stream->hash[5] = 0x9b05688c;
	stream->hash[6] = 0x1f83d9ab;
	stream->hash[7] = 0x5be0cd19;
	stream->hash_fn = sha256_stream_fn;
}

void			sha256_stream_file(int fd)
{
	t_sha2_stream	stream;
	uint8_t			buffer[4096];
	ssize_t			size_read;

	sha256_stream_init(&stream);
	hash_stream_begin((t_hash_stream *)&stream);
	while ((size_read = read(fd, buffer, sizeof(buffer))) > 0)
		hash_stream((t_hash_stream *)&stream, buffer, size_read);
	hash_stream_end((t_hash_stream *)&stream);
	sha256_print_digest(stream.hash);
}
