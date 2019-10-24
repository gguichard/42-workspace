/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_digest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 09:57:06 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/24 09:57:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include "ft_ssl_sha.h"
#include "utils.h"

void	sha512_digest(t_sha512_ctx *ctx)
{
	size_t	idx;

	idx = 0;
	while (idx < (ctx->digest_size / sizeof(uint64_t)))
	{
		ctx->hash.words[idx] = byte_swap64(ctx->hash.words[idx]);
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
