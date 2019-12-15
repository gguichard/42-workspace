/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:26:49 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/15 14:56:20 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"
#include "keystates.h"
#include "texture_inf.h"

void	wolf3d_main_menu(t_ctx *ctx)
{
	t_texture_inf	*text_inf;

	if (ctx->keystates & ESC_KEY)
		ctx->state = QUIT;
	else if (ctx->keystates & ENTER_KEY)
		ctx->state = PLAYING;
	else
	{
		text_inf = &ctx->textures[TEXTURE_MAIN_MENU];
		if (text_inf->width != ctx->window.size.width
			|| text_inf->height != ctx->window.size.height)
		{
			ft_memset(ctx->window.pixels, 0xFF, ctx->window.size.width
				* ctx->window.size.height
				* sizeof(*text_inf->pixels));
		}
		else
		{
			ft_memcpy(ctx->window.pixels, text_inf->pixels
				, text_inf->width * text_inf->height
				* sizeof(*text_inf->pixels));
		}
	}
}
