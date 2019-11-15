/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:28:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/15 17:33:30 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "libft.h"
#include "hash_stream.h"
#include "utils.h"

static void	hash_stream_len(t_hash_stream *stream, size_t count)
{
	uint64_t	len_bits_hi;
	uint64_t	len_bits_lo;

	len_bits_hi = stream->len_bits_hi;
	len_bits_lo = stream->len_bits_lo + count * 8;
	if (len_bits_lo < stream->len_bits_lo)
		len_bits_hi += 1;
	stream->len_bits_hi = len_bits_hi;
	stream->len_bits_lo = len_bits_lo;
}

void		hash_stream_begin(t_hash_stream *stream)
{
	stream->len_bits_hi = 0;
	stream->len_bits_lo = 0;
	stream->offset = 0;
}

void		hash_stream_end(t_hash_stream *stream)
{
	size_t	len;

	len = stream->offset;
	((uint8_t *)stream->block)[stream->offset] = (1 << 7);
	stream->offset += 1;
	if (stream->offset < stream->block_size)
		ft_memset(stream->block + stream->offset, 0
			, stream->block_size - stream->offset);
	if (stream->offset > (stream->block_size - stream->final_len_size))
	{
		stream->hash_fn(stream->ctx);
		stream->offset = 0;
		ft_memset(stream->block, 0
			, stream->block_size - stream->final_len_size);
	}
	hash_stream_len(stream, len);
	stream->final_fn(stream->ctx, stream->len_bits_hi, stream->len_bits_lo);
	stream->hash_fn(stream->ctx);
}

static int	hash_stream_buffer(t_hash_stream *stream
	, const uint8_t *bytes, size_t len)
{
	size_t	copy_len;

	copy_len = UTILS_MIN(len, stream->block_size - stream->offset);
	ft_memcpy(stream->block + stream->offset, bytes, copy_len);
	stream->offset += copy_len;
	if (stream->offset == stream->block_size)
	{
		stream->hash_fn(stream->ctx);
		hash_stream_len(stream, stream->block_size);
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
	while (len >= stream->block_size)
	{
		ft_memcpy(stream->block, bytes, stream->block_size);
		stream->hash_fn(stream->ctx);
		hash_stream_len(stream, stream->block_size);
		bytes += stream->block_size;
		len -= stream->block_size;
	}
	if (len != 0)
	{
		ft_memcpy(stream->block, bytes, len);
		stream->offset = len;
	}
}
