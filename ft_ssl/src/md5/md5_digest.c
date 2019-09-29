/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_digest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 22:40:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/29 12:17:07 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "libft.h"
#include "ft_ssl_md5.h"

void	md5_digest(char buffer[33], uint32_t hash[4])
{
	uint8_t	digest[16];
	size_t	idx;

	ft_memcpy(digest, hash, sizeof(digest));
	idx = 0;
	while (idx < 16)
	{
		sprintf(buffer + idx * 2, "%02x", digest[idx]);
		idx++;
	}
	buffer[32] = '\0';
}
