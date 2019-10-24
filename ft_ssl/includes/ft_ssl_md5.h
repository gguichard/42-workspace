/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:21:35 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/24 09:42:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include <stdint.h>
# include <string.h>
# include "hash_stream.h"

# define MD5_HASH_F(x, y, z) ((x & y) | (~x & z))
# define MD5_HASH_G(x, y, z) ((x & z) | (y & ~z))
# define MD5_HASH_H(x, y, z) (x ^ y ^ z)
# define MD5_HASH_I(x, y, z) (y ^ (x | ~z))

union			u_md5_hash
{
	uint32_t	words[4];
	uint8_t		bytes[16];
};

typedef struct	s_md5_ctx
{
	size_t				len;
	char				digest[33];
	uint32_t			words[16];
	union u_md5_hash	hash;
}				t_md5_ctx;

void			md5_stream_init(t_hash_stream *stream);
void			md5_stream(t_md5_ctx *ctx);
void			md5_final(t_md5_ctx *ctx, size_t offset);
void			md5_digest(t_md5_ctx *ctx);

#endif
