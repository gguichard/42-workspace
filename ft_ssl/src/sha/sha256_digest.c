/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_digest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:03:34 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/23 22:24:52 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "ft_ssl.h"
#include "ft_ssl_sha.h"

void	sha256_digest(t_sha256_ctx *ctx)
{
	size_t	idx;

	idx = 0;
	while (idx < (ctx->digest_size / sizeof(uint32_t)))
	{
		ctx->hash.words[idx] = byte_swap32(ctx->hash.words[idx]);
		idx++;
	}
	idx = 0;
	while (idx < ctx->digest_size)
	{
		digest_hex(ctx->digest + idx * 2, ctx->hash.bytes[idx]);
		idx++;
	}
	ctx->digest[idx * 2] = '\0';
}
