/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_md5.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:21:35 by gguichar          #+#    #+#             */
/*   Updated: 2020/02/28 10:39:37 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include <stdint.h>
# include "hash_stream.h"

# define MD5_HASH_FN "md5_hash_fn.c"

union			u_md5_hash
{
	uint32_t	words[4];
	uint8_t		bytes[16];
};

typedef struct	s_md5_ctx
{
	char				digest[33];
	uint32_t			words[16];
	union u_md5_hash	hash;
}				t_md5_ctx;

uint32_t		md5_hash_f(uint32_t x, uint32_t y, uint32_t z);
uint32_t		md5_hash_g(uint32_t x, uint32_t y, uint32_t z);
uint32_t		md5_hash_h(uint32_t x, uint32_t y, uint32_t z);
uint32_t		md5_hash_i(uint32_t x, uint32_t y, uint32_t z);

void			md5_stream_init(t_hash_stream *stream);
void			md5_stream(t_md5_ctx *ctx);
void			md5_final(t_md5_ctx *ctx
	, uint64_t len_bits_hi, uint64_t len_bits_lo);
void			md5_digest(t_md5_ctx *ctx);

#endif
