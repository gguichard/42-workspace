/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:28:09 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/27 23:20:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "wolf3d.h"
#include "keystates.h"
#include "player_inf.h"

static void	player_move(t_ctx *ctx)
{
	t_player_inf	*player_inf;

	player_inf = &ctx->player;
	// TODO: move player
}

void	wolf3d_play(t_ctx *ctx)
{
	if (ctx->keystates & ESC_KEY)
		ctx->state = MAIN_MENU;
	else
	{
		player_move(ctx);
		ft_memset(ctx->pixels, 0
			, ctx->window.size.width * ctx->window.size.height
				* sizeof(*ctx->pixels));
	}
}
