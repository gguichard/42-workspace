/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_stream.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:50:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/28 20:20:37 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "ft_ssl.h"
#include "ft_ssl_md5.h"

static void	md5_stream_fn(uint32_t hash[4], const uint8_t *bytes)
{
	size_t		idx;
	uint32_t	buffer[16];

	idx = 0;
	while (idx < (sizeof(buffer) / sizeof(buffer[0])))
	{
		buffer[idx] = bytes[idx * 4]
			| (bytes[idx * 4 + 1] << 8)
			| (bytes[idx * 4 + 2] << 16)
			| (bytes[idx * 4 + 3] << 24);
		idx++;
	}
	md5_roll(hash, buffer);
}

void		md5_stream_init(t_md5_stream *stream)
{
	stream->hash[0] = 0x67452301;
	stream->hash[1] = 0xefcdab89;
	stream->hash[2] = 0x98badcfe;
	stream->hash[3] = 0x10325476;
	stream->hash_fn = md5_stream_fn;
}

void		md5_stream_file(int fd)
{
	t_md5_stream	stream;
	uint8_t			buffer[4096];
	ssize_t			size_read;

	md5_stream_init(&stream);
	hash_stream_begin((t_hash_stream *)&stream);
	while ((size_read = read(fd, buffer, sizeof(buffer))) > 0)
		hash_stream((t_hash_stream *)&stream, buffer, size_read);
	hash_stream_end((t_hash_stream *)&stream);
	md5_print_digest(stream.hash);
}
