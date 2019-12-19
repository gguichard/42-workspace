/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 22:49:22 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/19 11:35:42 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL.h>
#include "libft.h"
#include "wolf3d.h"
#include "thread_inf.h"
#include "column_inf.h"
#include "tile_inf.h"
#include "texture_inf.h"
#include "ray_inf.h"

void		setup_draw_ctx(t_ctx *ctx, t_ray_inf *ray_inf, double fisheye_angle
	, t_draw_ctx *draw_ctx)
{
	if (ray_inf->length == 0.0)
		draw_ctx->wall_height = ctx->window.size.height;
	else
	{
		draw_ctx->wall_height = ctx->player.dist_to_proj
			/ (ray_inf->length * fisheye_angle);
	}
	draw_ctx->wall_height = round(draw_ctx->wall_height * 1.5 * 2) / 2;
	draw_ctx->wall_screen_height = ft_min(draw_ctx->wall_height
		, ctx->window.size.height);
	draw_ctx->wall_top = draw_ctx->wall_height / 2
		- draw_ctx->wall_screen_height / 2;
	draw_ctx->wall_screen_top = ctx->window.size.height / 2
		- draw_ctx->wall_screen_height / 2;
}

static void	draw_ray_list(t_ctx *ctx, t_column_inf *column_inf
	, t_ray_list *ray_list, double angle)
{
	t_ray_list	*ray_list_prev;

	while (ray_list != NULL)
	{
		ray_list_prev = ray_list->prev;
		if (ray_list_prev == NULL)
			minimap_ray(ctx, ray_list->ray_inf.length, angle);
		draw_column(ctx, column_inf, &ray_list->ray_inf);
		free(ray_list);
		ray_list = ray_list_prev;
	}
}

static void	player_view_thread(t_thread_inf *thread_inf)
{
	t_ctx			*ctx;
	int				half_width;
	t_column_inf	column_inf;
	double			angle;
	t_ray_list		*ray_list;

	ctx = (t_ctx *)thread_inf->data;
	half_width = ctx->window.size.width / 2;
	column_inf.x = thread_inf->x_start;
	while (column_inf.x < ctx->window.size.width)
	{
		angle = ctx->player.angle - atan((column_inf.x - half_width)
				/ ctx->player.dist_to_proj);
		ray_list = launch_ray(ctx->player.position, angle, &ctx->tile_map
			, FOG_DIST + 1);
		column_inf.fisheye_angle = cos(ctx->player.angle - angle);
		draw_ray_list(ctx, &column_inf, ray_list, angle);
		column_inf.x += THREADS_COUNT;
	}
}

void		player_view_raycast(t_ctx *ctx)
{
	t_thread_inf	threads[THREADS_COUNT];
	size_t			idx;

	idx = 0;
	while (idx < THREADS_COUNT)
	{
		threads[idx].data = ctx;
		threads[idx].x_start = idx;
		threads[idx].thread = SDL_CreateThread((void *)player_view_thread
				, "Wolf3D", &threads[idx]);
		idx++;
	}
	idx = 0;
	while (idx < THREADS_COUNT)
	{
		if (threads[idx].thread != NULL)
			SDL_WaitThread(threads[idx].thread, NULL);
		idx++;
	}
}
