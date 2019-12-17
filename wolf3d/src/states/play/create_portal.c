/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_portal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 07:59:14 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/17 18:34:30 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"
#include "wolf3d.h"
#include "ray_inf.h"
#include "tile_inf.h"

static int			is_ray_valid(t_ray_inf *ray_inf)
{
	return (ray_inf->tile != NULL && ray_inf->length < FOG_DIST);
}

static t_tile_meta	*search_portal(t_ctx *ctx, t_portal_type type)
{
	size_t	total_size;
	size_t	idx;

	total_size = ctx->tile_map.width * ctx->tile_map.height;
	idx = 0;
	while (idx < total_size)
	{
		if (ctx->tile_map.tiles[idx].type == PORTAL_DATA
			&& ctx->tile_map.tiles[idx].data.portal.type == type)
			return (&ctx->tile_map.tiles[idx]);
		idx++;
	}
	return (NULL);
}

static t_tile_meta	*search_opposite_portal(t_ctx *ctx, t_portal_type type)
{
	t_portal_type	opp_type;

	if (type == ENTRY_PORTAL)
		opp_type = EXIT_PORTAL;
	else
		opp_type = ENTRY_PORTAL;
	return (search_portal(ctx, opp_type));
}

static void			link_new_portal(t_ctx *ctx, t_ray_inf *ray_inf
	, t_portal_type type)
{
	t_tile_meta	*new_portal;

	new_portal = ray_inf->tile;
	new_portal->type = PORTAL_DATA;
	new_portal->data.portal.type = type;
	new_portal->data.portal.dir = ray_inf->direction;
	new_portal->data.portal.target = search_opposite_portal(ctx, type);
	if (new_portal->data.portal.target != NULL)
		new_portal->data.portal.target->data.portal.target = new_portal;
}

void				create_portal(t_ctx *ctx, t_portal_type type)
{
	t_ray_list	*ray_list;
	t_tile_meta	*prev_portal;

	ray_list = launch_ray(ctx->player.position, ctx->player.angle
		, &ctx->tile_map, 2);
	if (ray_list == NULL)
		return ;
	if (is_ray_valid(&ray_list->ray_inf))
	{
		prev_portal = search_portal(ctx, type);
		if (prev_portal != NULL)
		{
			prev_portal->type = NO_DATA;
			if (is_colliding(ctx->player.position, &ctx->tile_map
				, prev_portal->data.portal.dir))
			{
				prev_portal->type = PORTAL_DATA;
				return ;
			}
			ft_memset(&prev_portal->data, 0, sizeof(prev_portal->data));
		}
		link_new_portal(ctx, &ray_list->ray_inf, type);
	}
	free_ray_list(ray_list);
}
