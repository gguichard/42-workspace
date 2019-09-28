/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:21:35 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/28 14:28:33 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include <stdint.h>
# include <string.h>

# define MD5_HASH_F(x, y, z) ((x & y) | (~x & z))
# define MD5_HASH_G(x, y, z) ((x & z) | (y & ~z))
# define MD5_HASH_H(x, y, z) (x ^ y ^ z)
# define MD5_HASH_I(x, y, z) (y ^ (x | ~z))

typedef struct	s_md5_stream
{
	size_t		len;
	size_t		total_len;
	uint8_t		buffer[64];
	size_t		offset;
	void		(*hash_fn)(struct s_md5_stream *
		, const uint8_t *, size_t, size_t);
	uint32_t	hash[4];
}				t_md5_stream;

void			md5_stream_init(t_md5_stream *stream);
void			md5_process_words(uint32_t hash[4], uint32_t words[16]);

void			md5_hash(const uint8_t *bytes, size_t len);
void			md5_stream_file(int fd);
void			md5_print_digest(uint32_t hash[4]);

#endif
