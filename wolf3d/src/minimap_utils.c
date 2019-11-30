/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 13:17:42 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/30 14:33:07 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdint.h>
#include "libft.h"
#include "wolf3d.h"
#include "minimap_inf.h"

void	minimap_destroy(t_minimap_inf *minimap)
{
	ft_memdel((void *)&minimap->pixels);
	ft_memdel((void *)&minimap->z_buffer);
}

void	minimap_reset_z_buffer(t_ctx *ctx)
{
	size_t	total_size;

	total_size = ctx->minimap.size * ctx->minimap.size;
	ft_memset(ctx->minimap.z_buffer, 0xff, total_size
		* sizeof(*ctx->minimap.z_buffer));
}

void	draw_minimap_view(t_ctx *ctx)
{
	int	y;

	y = 0;
	while (y < ctx->minimap.size)
	{
		ft_memcpy(&ctx->window.pixels[(y + MINIMAP_OFFSET_Y)
				* ctx->window.size.width + MINIMAP_OFFSET_X]
			, ctx->minimap.pixels + y * ctx->minimap.size
			, ctx->minimap.size * sizeof(uint32_t));
		y++;
	}
}
