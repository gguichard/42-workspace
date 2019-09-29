/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_digest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:03:34 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/29 15:54:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "ft_ssl.h"
#include "ft_ssl_sha2.h"

void	sha256_digest(char buffer[65], uint32_t hash[8])
{
	uint8_t	digest[32];
	size_t	idx;

	idx = 0;
	while (idx < 8)
	{
		digest[idx * 4] = (hash[idx] >> 24) & 0xff;
		digest[idx * 4 + 1] = (hash[idx] >> 16) & 0xff;
		digest[idx * 4 + 2] = (hash[idx] >> 8) & 0xff;
		digest[idx * 4 + 3] = hash[idx] & 0xff;
		idx++;
	}
	idx = 0;
	while (idx < 32)
	{
		digest_hex(buffer + idx * 2, digest[idx]);
		idx++;
	}
	buffer[64] = '\0';
}
