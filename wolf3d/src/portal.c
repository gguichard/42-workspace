/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:08:33 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/17 17:33:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "wolf3d.h"
#include "ray_inf.h"
#include "map_inf.h"
#include "tile_inf.h"
#include "direction.h"
#include "vec2.h"

double			get_portal_angle_diff(t_portal_inf *portal
	, t_portal_inf *target)
{
	double	angle;

	if (target->dir == portal->dir)
		angle = M_PI;
	else if ((portal->dir == NORTH && target->dir == WEST)
		|| (portal->dir == SOUTH && target->dir == EAST)
		|| (portal->dir == WEST && target->dir == SOUTH)
		|| (portal->dir == EAST && target->dir == NORTH))
		angle = M_PI / 2;
	else if ((portal->dir == NORTH && target->dir == EAST)
		|| (portal->dir == SOUTH && target->dir == WEST)
		|| (portal->dir == WEST && target->dir == NORTH)
		|| (portal->dir == EAST && target->dir == SOUTH))
		angle = -M_PI / 2;
	else
		angle = 0;
	return (angle);
}

t_vec2d			get_portal_launch_origin(t_direction hit_dir
	, double hit_position, t_tile_meta *target)
{
	double	position;
	t_vec2d	origin;

	position = hit_position;
	if (hit_dir == target->data.portal.dir
		|| (hit_dir == NORTH && target->data.portal.dir == EAST)
		|| (hit_dir == EAST && target->data.portal.dir == NORTH)
		|| (hit_dir == SOUTH && target->data.portal.dir == WEST)
		|| (hit_dir == WEST && target->data.portal.dir == SOUTH))
		position = 1 - position;
	origin = vec2d(target->pos.x, target->pos.y);
	if (target->data.portal.dir == SOUTH)
		origin.x += 1;
	else if (target->data.portal.dir == EAST)
		origin.y += 1;
	if (target->data.portal.dir == NORTH
		|| target->data.portal.dir == SOUTH)
		origin.y += position;
	else if (target->data.portal.dir == EAST
		|| target->data.portal.dir == WEST)
		origin.x += position;
	return (origin);
}

static t_vec2d	get_offset(t_vec2d pos, t_direction dir, t_direction t_dir)
{
	t_vec2d	offset;

	if (dir == NORTH || dir == WEST)
		offset = vec2d(pos.x - floor(pos.x), pos.y - floor(pos.y));
	else if (dir == SOUTH)
		offset = vec2d(floor(pos.x + 1) - pos.x, pos.y - floor(pos.y));
	else if (dir == EAST)
		offset = vec2d(pos.x - floor(pos.x), floor(pos.y + 1) - pos.y);
	else
		offset = vec2d(0, 0);
	if ((t_dir == NORTH && dir == EAST) || (t_dir == SOUTH && dir == WEST))
		offset = vec2d(offset.y, 1 - offset.x);
	else if ((t_dir == WEST && dir == SOUTH) || (t_dir == EAST && dir == NORTH))
		offset = vec2d(1 - offset.y, offset.x);
	else if ((t_dir == NORTH && dir == WEST) || (t_dir == WEST && dir == NORTH)
		|| (t_dir == SOUTH && dir == EAST) || (t_dir == EAST && dir == SOUTH))
		offset = vec2d(offset.y, offset.x);
	else if (t_dir == dir)
	{
		if (t_dir == NORTH || t_dir == SOUTH)
			offset = vec2d(offset.x, 1 - offset.y);
		else if (t_dir == WEST || t_dir == EAST)
			offset = vec2d(1 - offset.x, offset.y);
	}
	return (offset);
}

void			teleport_through_portal(t_ctx *ctx, t_tile_meta *tile)
{
	t_tile_meta	*target;
	t_vec2d		offset;
	t_vec2d		pos;
	double		angle_diff;

	target = tile->data.portal.target;
	offset = get_offset(ctx->player.position
		, tile->data.portal.dir, target->data.portal.dir);
	if (target->data.portal.dir == NORTH)
		pos = vec2d(target->pos.x - offset.x, target->pos.y + offset.y);
	else if (target->data.portal.dir == SOUTH)
		pos = vec2d(target->pos.x + 1 + offset.x, target->pos.y + offset.y);
	else if (target->data.portal.dir == WEST)
		pos = vec2d(target->pos.x + offset.x, target->pos.y - offset.y);
	else if (target->data.portal.dir == EAST)
		pos = vec2d(target->pos.x + offset.x, target->pos.y + 1 + offset.y);
	else
		pos = vec2d(0, 0);
	angle_diff = get_portal_angle_diff(&tile->data.portal
		, &target->data.portal);
	ctx->player.angle += angle_diff;
	ctx->player.velocity = vec2d_rotate(ctx->player.velocity, angle_diff);
	ctx->player.position = pos;
}
