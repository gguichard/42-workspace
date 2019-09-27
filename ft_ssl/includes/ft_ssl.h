/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:17:49 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/28 01:15:39 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdint.h>
# include <string.h>

# define UTILS_MIN(x, y) (x > y ? y : x)
# define UTILS_ROTATELEFT(n, s) (((n) << s) | ((n) >> (sizeof(n) * 8 - s)))
# define UTILS_ROTATERIGHT(n, s) (((n) >> s) | ((n) << (sizeof(n) * 8 - s)))

typedef struct	s_hash_stream
{
	size_t		len;
	size_t		total_len;
	uint8_t		buffer[64];
	size_t		offset;
	void		(*hash_fn)(struct s_hash_stream *
		, const uint8_t *, size_t, size_t);
	uint32_t	hash[0];
}				t_hash_stream;

void			hash_stream_begin(t_hash_stream *stream);
void			hash_stream_end(t_hash_stream *stream);
void			hash_stream(t_hash_stream *stream
	, const uint8_t *bytes, size_t len);

size_t			align_up(size_t n, int mod);

#endif
