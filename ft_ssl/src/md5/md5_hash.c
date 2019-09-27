/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:19:33 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/28 01:12:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "ft_ssl.h"
#include "ft_ssl_md5.h"

static t_md5_step	g_md5_steps[64] = {
	/* F(b, c, d) */
	{0, 7, 0xd76aa478}, {1, 12, 0xe8c7b756}
		, {2, 17, 0x242070db}, {3, 22, 0xc1bdceee},
	{4, 7, 0xf57c0faf}, {5, 12, 0x4787c62a}
		, {6, 17, 0xa8304613}, {7, 22, 0xfd469501},
	{8, 7, 0x698098d8}, {9, 12, 0x8b44f7af}
		, {10, 17, 0xffff5bb1}, {11, 22, 0x895cd7be},
	{12, 7, 0x6b901122}, {13, 12, 0xfd987193}
		, {14, 17, 0xa679438e}, {15, 22, 0x49b40821},
	/* G(b, c, d) */
	{1, 5, 0xf61e2562}, {6, 9, 0xc040b340}
		, {11, 14, 0x265e5a51}, {0, 20, 0xe9b6c7aa},
	{5, 5, 0xd62f105d}, {10, 9, 0x2441453}
		, {15, 14, 0xd8a1e681}, {4, 20, 0xe7d3fbc8},
	{9, 5, 0x21e1cde6}, {14, 9, 0xc33707d6}
		, {3, 14, 0xf4d50d87}, {8, 20, 0x455a14ed},
	{13, 5, 0xa9e3e905}, {2, 9, 0xfcefa3f8}
		, {7, 14, 0x676f02d9}, {12, 20, 0x8d2a4c8a},
	/* H(b, c, d) */
	{5, 4, 0xfffa3942}, {8, 11, 0x8771f681}
		, {11, 16, 0x6d9d6122}, {14, 23, 0xfde5380c},
	{1, 4, 0xa4beea44}, {4, 11, 0x4bdecfa9}
		, {7, 16, 0xf6bb4b60}, {10, 23, 0xbebfbc70},
	{13, 4, 0x289b7ec6}, {0, 11, 0xeaa127fa}
		, {3, 16, 0xd4ef3085}, {6, 23, 0x4881d05},
	{9, 4, 0xd9d4d039}, {12, 11, 0xe6db99e5}
		, {15, 16, 0x1fa27cf8}, {2, 23, 0xc4ac5665},
	/* I(b, c, d) */
	{0, 6, 0xf4292244}, {7, 10, 0x432aff97}
		, {14, 15, 0xab9423a7}, {5, 21, 0xfc93a039},
	{12, 6, 0x655b59c3}, {3, 10, 0x8f0ccc92}
		, {10, 15, 0xffeff47d}, {1, 21, 0x85845dd1},
	{8, 6, 0x6fa87e4f}, {15, 10, 0xfe2ce6e0}
		, {6, 15, 0xa3014314}, {13, 21, 0x4e0811a1},
	{4, 6, 0xf7537e82}, {11, 10, 0xbd3af235}
		, {2, 15, 0x2ad7d2bb}, {9, 21, 0xeb86d391}
};

static void		md5_steps(uint32_t words[16], uint32_t output[4])
{
	size_t		idx;
	uint32_t	value;
	t_md5_step	*step;

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
		step = &g_md5_steps[idx];
		value += output[0] + words[step->word_index] + step->sine;
		output[0] = output[3];
		output[3] = output[2];
		output[2] = output[1];
		output[1] += UTILS_ROTATELEFT(value, step->shift_rotate);
		idx++;
	}
}

void			md5_process_words(uint32_t hash[4], uint32_t words[16])
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

void			md5_hash(const uint8_t *bytes, size_t len)
{
	t_md5_stream	stream;

	stream.hash[0] = 0x67452301;
	stream.hash[1] = 0xefcdab89;
	stream.hash[2] = 0x98badcfe;
	stream.hash[3] = 0x10325476;
	stream.hash_fn = md5_stream_fn;
	hash_stream_begin((t_hash_stream *)&stream);
	hash_stream((t_hash_stream *)&stream, bytes, len);
	hash_stream_end((t_hash_stream *)&stream);
	md5_print_digest(stream.hash);
}
