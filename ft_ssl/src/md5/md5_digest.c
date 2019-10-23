/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_digest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 22:40:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/23 21:35:29 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "ft_ssl.h"
#include "ft_ssl_md5.h"

void	md5_digest(t_md5_ctx *ctx)
{
	size_t	idx;

	idx = 0;
	while (idx < sizeof(ctx->hash))
	{
		digest_hex(ctx->digest + idx * 2, ctx->hash.bytes[idx]);
		idx++;
	}
	ctx->digest[idx * 2] = '\0';
}
