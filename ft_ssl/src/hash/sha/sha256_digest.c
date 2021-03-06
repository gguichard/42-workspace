/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_digest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:03:34 by gguichar          #+#    #+#             */
/*   Updated: 2020/02/28 10:42:29 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "hash_sha.h"
#include "utils.h"

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
