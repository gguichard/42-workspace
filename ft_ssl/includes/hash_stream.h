/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_stream.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 09:37:43 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/24 10:57:33 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_STREAM_H
# define HASH_STREAM_H

# include <stdint.h>
# include <string.h>

typedef struct	s_hash_stream
{
	void		*ctx;
	uint8_t		*ctx_buffer;
	size_t		block_size;
	size_t		final_len_size;
	char		*digest_buffer;
	void		(*hash_fn)(void *);
	void		(*final_fn)(void *, size_t);
	void		(*digest_fn)(void *);
	size_t		offset;
	size_t		len;
}				t_hash_stream;

void			hash_stream_begin(t_hash_stream *stream);
void			hash_stream_end(t_hash_stream *stream);
void			hash_stream(t_hash_stream *stream
	, const uint8_t *bytes, size_t len);

char			*hash_stream_bytes(void (*init_fn)(t_hash_stream *)
	, const uint8_t *bytes, size_t len);
char			*hash_stream_file(void (*init_fn)(t_hash_stream *)
	, int fd, int in_out);

#endif
