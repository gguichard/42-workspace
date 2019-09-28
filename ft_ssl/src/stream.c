/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:28:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/28 20:58:16 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "libft.h"
#include "ft_ssl.h"

void		hash_stream_begin(t_hash_stream *stream)
{
	stream->len = 0;
	stream->offset = 0;
}

void		hash_stream_end(t_hash_stream *stream)
{
	uint64_t	total_len;

	stream->len += stream->offset;
	stream->buffer[stream->offset] = (1 << 7);
	stream->offset += 1;
	if (stream->offset < 64)
		ft_memset(stream->buffer + stream->offset, 0, 64 - stream->offset);
	if (stream->offset > 56)
	{
		stream->hash_fn(stream->hash, stream->buffer);
		stream->offset = 0;
		ft_memset(stream->buffer, 0, 56);
	}
	total_len = stream->len * 8;
	ft_memcpy(stream->buffer + 56, &total_len, 8);
	stream->hash_fn(stream->hash, stream->buffer);
}

static int	hash_stream_buffer(t_hash_stream *stream
	, const uint8_t *bytes, size_t len)
{
	size_t	copy_len;

	copy_len = UTILS_MIN(len, 64 - stream->offset);
	ft_memcpy(stream->buffer + stream->offset, bytes, copy_len);
	stream->offset += copy_len;
	if (stream->offset == 64)
	{
		stream->hash_fn(stream->hash, stream->buffer);
		stream->len += stream->offset;
		stream->offset = 0;
	}
	return (copy_len);
}

void		hash_stream(t_hash_stream *stream
	, const uint8_t *bytes, size_t len)
{
	size_t	offset;

	if (stream->offset != 0)
	{
		offset = hash_stream_buffer(stream, bytes, len);
		bytes += offset;
		len -= offset;
	}
	while (len >= 64)
	{
		stream->hash_fn(stream->hash, bytes);
		stream->len += 64;
		bytes += 64;
		len -= 64;
	}
	if (len != 0)
	{
		ft_memcpy(stream->buffer, bytes, len);
		stream->offset = len;
	}
}
