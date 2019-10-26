/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 23:24:32 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/26 12:47:28 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "utils.h"

uint32_t	byte_swap32(uint32_t x)
{
	x = ((x << 8) & 0xff00ff00) | ((x >> 8) & 0x00ff00ff);
	x = (x << 16) | (x >> 16);
	return (x);
}

uint64_t	byte_swap64(uint64_t x)
{
	x = ((x & 0x00000000ffffffff) << 32) | ((x & 0xffffffff00000000) >> 32);
	x = ((x & 0x0000ffff0000ffff) << 16) | ((x & 0xffff0000ffff0000) >> 16);
	x = ((x & 0x00ff00ff00ff00ff) << 8) | ((x & 0xff00ff00ff00ff00) >> 8);
	return (x);
}

void		digest_hex(char buffer[2], uint8_t byte)
{
	buffer[0] = "0123456789abcdef"[byte >> 4];
	buffer[1] = "0123456789abcdef"[byte & 0xf];
}
