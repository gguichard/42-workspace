/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:26:49 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/15 14:19:19 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"
#include "keystates.h"

void	wolf3d_main_menu(t_ctx *ctx)
{
	if (ctx->keystates & ESC_KEY)
		ctx->state = QUIT;
	else if (ctx->keystates & ENTER_KEY)
		ctx->state = PLAYING;
	else
	{
		ft_memcpy(ctx->window.pixels, ctx->textures[TEXTURE_MAIN_MENU].pixels
			, ctx->window.size.width * ctx->window.size.height
			* sizeof(*ctx->window.pixels));
	}
}
