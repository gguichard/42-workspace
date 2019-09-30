/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:19:33 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/30 22:43:42 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "ft_ssl.h"
#include "ft_ssl_md5.h"

static const int		g_md5_k[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12,
	5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
	0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9
};

static const int		g_md5_s[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

static const uint32_t	g_md5_t[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x2441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x4881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static void	md5_steps(uint32_t words[16], uint32_t output[4])
{
	size_t		idx;
	uint32_t	value;

	idx = 0;
	while (idx < 64)
	{
		if (idx < 16)
			value = MD5_HASH_F(output[1], output[2], output[3]);
		else if (idx < 32)
			value = MD5_HASH_G(output[1], output[2], output[3]);
		else if (idx < 48)
			value = MD5_HASH_H(output[1], output[2], output[3]);
		else
			value = MD5_HASH_I(output[1], output[2], output[3]);
		value += output[0] + words[g_md5_k[idx]] + g_md5_t[idx];
		output[0] = output[3];
		output[3] = output[2];
		output[2] = output[1];
		output[1] += UTILS_ROTATELEFT(value, g_md5_s[idx]);
		idx++;
	}
}

void		md5_roll(uint32_t hash[4], uint32_t words[16])
{
	uint32_t	values[4];

	values[0] = hash[0];
	values[1] = hash[1];
	values[2] = hash[2];
	values[3] = hash[3];
	md5_steps(words, values);
	hash[0] += values[0];
	hash[1] += values[1];
	hash[2] += values[2];
	hash[3] += values[3];
}

void		md5_hash(char digest[33], const uint8_t *bytes, size_t len)
{
	t_md5_stream	stream;

	md5_stream_init(&stream);
	hash_stream_begin((t_hash_stream *)&stream);
	hash_stream((t_hash_stream *)&stream, bytes, len);
	hash_stream_end((t_hash_stream *)&stream);
	md5_digest(digest, stream.hash);
}
