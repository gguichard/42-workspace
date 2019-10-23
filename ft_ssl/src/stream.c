/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:28:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/23 23:45:50 by gguichar         ###   ########.fr       */
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
	size_t	offset;

	offset = stream->offset;
	stream->ctx_buffer[stream->offset] = (1 << 7);
	stream->offset += 1;
	if (stream->offset < stream->ctx_buffer_size)
		ft_memset(stream->ctx_buffer + stream->offset, 0
			, stream->ctx_buffer_size - stream->offset);
	if (stream->offset > (stream->ctx_buffer_size - stream->final_len_size))
	{
		stream->hash_fn(stream->ctx);
		stream->offset = 0;
		ft_memset(stream->ctx_buffer, 0
			, stream->ctx_buffer_size - stream->final_len_size);
	}
	stream->final_fn(stream->ctx, offset);
	stream->hash_fn(stream->ctx);
}

static int	hash_stream_buffer(t_hash_stream *stream
	, const uint8_t *bytes, size_t len)
{
	size_t	copy_len;

	copy_len = UTILS_MIN(len, stream->ctx_buffer_size - stream->offset);
	ft_memcpy(stream->ctx_buffer + stream->offset, bytes, copy_len);
	stream->offset += copy_len;
	if (stream->offset == stream->ctx_buffer_size)
	{
		stream->hash_fn(stream->ctx);
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
	while (len >= stream->ctx_buffer_size)
	{
		ft_memcpy(stream->ctx_buffer, bytes, stream->ctx_buffer_size);
		stream->hash_fn(stream->ctx);
		stream->len += stream->ctx_buffer_size;
		bytes += stream->ctx_buffer_size;
		len -= stream->ctx_buffer_size;
	}
	if (len != 0)
	{
		ft_memcpy(stream->ctx_buffer, bytes, len);
		stream->offset = len;
	}
}
