/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:26:49 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/27 23:08:54 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"
#include "keystates.h"

void	wolf3d_main_menu(t_ctx *ctx)
{
	if (ctx->keystates & ENTER_KEY)
	{
		ctx->player = ctx->tile_map.player;
		ctx->state = PLAYING;
	}
	else
	{
		ft_memset(ctx->pixels, 255
			, ctx->window.size.width * ctx->window.size.height
				* sizeof(*ctx->pixels));
	}
}
