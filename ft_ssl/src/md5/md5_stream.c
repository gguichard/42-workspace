/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_stream.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:50:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/28 01:12:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "ft_ssl.h"
#include "ft_ssl_md5.h"

static uint8_t	md5_byte(const uint8_t *bytes, size_t len, size_t index)
{
	if (index < len)
		return (bytes[index]);
	else if (index == len)
		return (1 << 7);
	else
		return (0);
}

void			md5_stream_fn(t_md5_stream *stream
	, const uint8_t *bytes, size_t len, size_t offset)
{
	size_t		idx;
	uint32_t	buffer[16];

	idx = 0;
	while (idx < (sizeof(buffer) / sizeof(buffer[0])))
	{
		if (offset <= len)
			buffer[idx] = (uint32_t)md5_byte(bytes, len, offset)
					| ((uint32_t)md5_byte(bytes, len, offset + 1) << 8)
					| ((uint32_t)md5_byte(bytes, len, offset + 2) << 16)
					| ((uint32_t)md5_byte(bytes, len, offset + 3) << 24);
		else if ((offset + 4) == stream->total_len)
			buffer[idx] = (len * 8) << 32;
		else if ((offset + 8) == stream->total_len)
			buffer[idx] = (len * 8) & 0xffffffff;
		else
			buffer[idx] = 0;
		offset += 4;
		idx++;
	}
	md5_process_words(stream->hash, buffer);
}

void			md5_stream_file(int fd)
{
	t_md5_stream	stream;
	uint8_t			buffer[4096];
	ssize_t			size_read;

	stream.hash[0] = 0x67452301;
	stream.hash[1] = 0xefcdab89;
	stream.hash[2] = 0x98badcfe;
	stream.hash[3] = 0x10325476;
	stream.hash_fn = md5_stream_fn;
	hash_stream_begin((t_hash_stream *)&stream);
	while ((size_read = read(fd, buffer, sizeof(buffer))) > 0)
		hash_stream((t_hash_stream *)&stream, buffer, size_read);
	hash_stream_end((t_hash_stream *)&stream);
	md5_print_digest(stream.hash);
}
