/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1_digest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 11:10:03 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/23 22:31:07 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "ft_ssl.h"
#include "ft_ssl_sha.h"

void	sha1_digest(t_sha1_ctx *ctx)
{
	size_t	idx;

	idx = 0;
	while (idx < (sizeof(ctx->hash) / sizeof(uint32_t)))
	{
		ctx->hash.words[idx] = byte_swap32(ctx->hash.words[idx]);
		idx++;
	}
	idx = 0;
	while (idx < sizeof(ctx->hash))
	{
		digest_hex(ctx->digest + idx * 2, ctx->hash.bytes[idx]);
		idx++;
	}
	ctx->digest[idx * 2] = '\0';
}
