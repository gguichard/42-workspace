/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:26:49 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/10 12:46:21 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "wolf3d.h"
#include "keystates.h"

void	wolf3d_main_menu(t_ctx *ctx)
{
	if (ctx->keystates & ENTER_KEY)
	{
		ctx->player = ctx->tile_map.player;
		ctx->player.fov = (90 / 360.) * M_PI;
		ctx->player.dist_to_proj = (ctx->window.size.width / 2)
			/ tan(ctx->player.fov / 2);
		ctx->state = PLAYING;
	}
	else
	{
		ft_memset(ctx->window.pixels, 255
			, ctx->window.size.width * ctx->window.size.height
				* sizeof(*ctx->window.pixels));
	}
}
