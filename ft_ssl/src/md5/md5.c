/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:19:33 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/26 22:45:04 by gguichar         ###   ########.fr       */
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

static inline uint8_t	md5_byte(const uint8_t *bytes, size_t len, size_t index)
{
	if (index < len)
		return (bytes[index]);
	else if (index == len)
		return (1 << 7);
	else
		return (0);
}

static inline void		md5_decode(const uint8_t *bytes
	, size_t len, size_t total_len
	, uint32_t buffer[16], size_t offset)
{
	size_t	idx;

	idx = 0;
	while (idx < 16)
	{
		if (offset <= len)
			buffer[idx] = (uint32_t)md5_byte(bytes, len, offset)
					| ((uint32_t)md5_byte(bytes, len, offset + 1) << 8)
					| ((uint32_t)md5_byte(bytes, len, offset + 2) << 16)
					| ((uint32_t)md5_byte(bytes, len, offset + 3) << 24);
		else if ((offset + 4) == total_len)
			buffer[idx] = (len * 8) << 32;
		else if ((offset + 8) == total_len)
			buffer[idx] = (len * 8) & 0xffffffff;
		else
			buffer[idx] = 0;
		offset += 4;
		idx++;
	}
}

static inline void		md5_steps(uint32_t words[16], uint32_t output[4])
{
	size_t		idx;
	uint32_t	value;
	t_md5_step	*step;

	idx = 0;
	while (idx < 64)
	{
		if (idx < 16)
			value = MD5_FUN_F(output[1], output[2], output[3]);
		else if (idx < 32)
			value = MD5_FUN_G(output[1], output[2], output[3]);
		else if (idx < 48)
			value = MD5_FUN_H(output[1], output[2], output[3]);
		else
			value = MD5_FUN_I(output[1], output[2], output[3]);
		step = &g_md5_steps[idx];
		value += output[0] + words[step->word_index] + step->sine;
		output[0] = output[3];
		output[3] = output[2];
		output[2] = output[1];
		output[1] += MD5_ROTATELEFT(value, step->shift_rotate);
		idx++;
	}
}

static inline void		md5_process_words(uint32_t states[4]
	, uint32_t words[16])
{
	uint32_t	values[4];

	values[0] = states[0];
	values[1] = states[1];
	values[2] = states[2];
	values[3] = states[3];
	md5_steps(words, values);
	states[0] += values[0];
	states[1] += values[1];
	states[2] += values[2];
	states[3] += values[3];
}

void					md5_hash(const uint8_t *bytes, size_t len)
{
	size_t		total_len;
	uint32_t	states[4];
	size_t		idx;
	uint32_t	words[16];

	total_len = align_up(len, 64);
	if ((total_len - len) <= 8)
		total_len += 64;
	states[0] = 0x67452301;
	states[1] = 0xefcdab89;
	states[2] = 0x98badcfe;
	states[3] = 0x10325476;
	idx = 0;
	while (idx < total_len)
	{
		md5_decode(bytes, len, total_len, words, idx);
		md5_process_words(states, words);
		idx += 64;
	}
	md5_print_digest(states);
}
