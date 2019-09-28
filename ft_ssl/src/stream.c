/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:28:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/28 11:33:26 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "libft.h"
#include "ft_ssl.h"

void		hash_stream_begin(t_hash_stream *stream)
{
	stream->len = 0;
	stream->total_len = ~((size_t)0);
	stream->offset = 0;
}

void		hash_stream_end(t_hash_stream *stream)
{
	size_t	len;
	size_t	total_len;

	len = stream->len + stream->offset;
	total_len = align_up(len, 64);
	if ((total_len - len) <= 8)
		total_len += 64;
	stream->total_len = total_len;
	while (stream->len < total_len)
	{
		stream->hash_fn(stream, stream->buffer - stream->len, len, stream->len);
		stream->len += 64;
	}
}

static void	hash_stream_buffer(t_hash_stream *stream
	, const uint8_t *bytes, size_t len)
{
	size_t	copy_len;

	copy_len = UTILS_MIN(len, sizeof(stream->buffer) - stream->offset);
	ft_memcpy(stream->buffer, bytes, copy_len);
	stream->offset += copy_len;
	bytes += copy_len;
	len -= copy_len;
	if (stream->offset == sizeof(stream->buffer))
	{
		stream->hash_fn(stream, stream->buffer, ~((size_t)0), 0);
		stream->len += stream->offset;
		stream->offset = 0;
	}
}

void		hash_stream(t_hash_stream *stream
	, const uint8_t *bytes, size_t len)
{
	if (stream->offset != 0)
		hash_stream_buffer(stream, bytes, len);
	while (len > 64)
	{
		stream->hash_fn(stream, bytes, ~((size_t)0), 0);
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
