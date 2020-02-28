/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 22:55:09 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/24 09:43:23 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "hash_stream.h"

char	*hash_stream_bytes(void (*init_fn)(t_hash_stream *)
	, const uint8_t *bytes, size_t len)
{
	t_hash_stream	stream;

	init_fn(&stream);
	hash_stream_begin(&stream);
	hash_stream(&stream, bytes, len);
	hash_stream_end(&stream);
	stream.digest_fn(stream.ctx);
	return (stream.digest_buffer);
}

char	*hash_stream_file(void (*init_fn)(t_hash_stream *)
	, int fd, int in_out)
{
	t_hash_stream	stream;
	uint8_t			read_buffer[4096];
	ssize_t			size_read;

	init_fn(&stream);
	hash_stream_begin(&stream);
	while ((size_read = read(fd, read_buffer, sizeof(read_buffer))) > 0)
	{
		if (in_out)
			write(STDOUT_FILENO, read_buffer, size_read);
		hash_stream(&stream, read_buffer, size_read);
	}
	if (size_read == -1)
		return (NULL);
	hash_stream_end(&stream);
	stream.digest_fn(stream.ctx);
	return (stream.digest_buffer);
}
