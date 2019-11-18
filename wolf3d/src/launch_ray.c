/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:18:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/19 23:19:19 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "wolf3d.h"
#include "ray_inf.h"
#include "map_inf.h"
#include "tile_inf.h"
#include "vec2.h"
#include "direction.h"

static void			init_ray_inf(t_ray_inf *ray_inf, t_vec2d origin)
{
	ft_memset(ray_inf, 0, sizeof(t_ray_inf));
	ray_inf->origin = origin;
	ray_inf->length = INFINITY;
}

static t_tile_meta	*get_map_tile(int x, int y, t_map_inf *map_inf)
{
	if (x < 0 || x >= map_inf->width || y < 0 || y >= map_inf->height)
		return (NULL);
	else
		return (&map_inf->tiles[y * map_inf->width + x]);
}

static void			launch_hray(t_ray_inf *ray_inf, t_vec2d delta, double slope
	, t_map_inf *map_inf)
{
	t_vec2d		pos;
	t_tile_meta	*tile;
	double		dumb;

	pos.x = floor(ray_inf->origin.x + (delta.x > 0 ? 1 : 0));
	pos.y = ray_inf->origin.y + fabs(pos.x - ray_inf->origin.x) * slope;
	while (1)
	{
		tile = get_map_tile(pos.x + (delta.x > 0 ? 0 : -1), pos.y, map_inf);
		if (tile == NULL || tile->id != TILE_EMPTY)
			break ;
		pos.x += (delta.x > 0 ? 1 : -1);
		pos.y += slope;
	}
	ray_inf->position = modf(pos.y, &dumb);
	if (ray_inf->position < 0)
		ray_inf->position += 1;
	ray_inf->direction = (delta.x > 0 ? NORTH : SOUTH);
	ray_inf->tile = tile;
	ray_inf->length = sqrt(pow(pos.x - ray_inf->origin.x, 2)
			+ pow(pos.y - ray_inf->origin.y, 2));
}

static void			launch_vray(t_ray_inf *ray_inf, t_vec2d delta, double slope
	, t_map_inf *map_inf)
{
	t_vec2d		pos;
	t_tile_meta	*tile;
	double		dumb;

	pos.y = floor(ray_inf->origin.y + (delta.y > 0 ? 1 : 0));
	pos.x = ray_inf->origin.x + fabs(pos.y - ray_inf->origin.y) * slope;
	while (1)
	{
		tile = get_map_tile(pos.x, pos.y + (delta.y > 0 ? 0 : -1), map_inf);
		if (tile == NULL || tile->id != TILE_EMPTY)
			break ;
		pos.y += (delta.y > 0 ? 1 : -1);
		pos.x += slope;
	}
	ray_inf->position = modf(pos.x, &dumb);
	if (ray_inf->position < 0)
		ray_inf->position += 1;
	ray_inf->direction = (delta.y > 0 ? WEST : EAST);
	ray_inf->tile = tile;
	ray_inf->length = sqrt(pow(pos.x - ray_inf->origin.x, 2)
		+ pow(pos.y - ray_inf->origin.y, 2));
}

t_ray_inf			launch_ray(t_vec2d origin, double angle, t_map_inf *map_inf)
{
	t_ray_inf	hori_ray_inf;
	t_ray_inf	vert_ray_inf;
	t_vec2d		delta;

	delta = vec2d(cos(angle), -sin(angle));
	init_ray_inf(&vert_ray_inf, origin);
	init_ray_inf(&hori_ray_inf, origin);
	if (fabs(delta.x) != 0.0)
		launch_hray(&hori_ray_inf, delta, delta.y / fabs(delta.x), map_inf);
	if (fabs(delta.y) != 0.0)
		launch_vray(&vert_ray_inf, delta, delta.x / fabs(delta.y), map_inf);
	if (vert_ray_inf.length < hori_ray_inf.length)
		return (vert_ray_inf);
	else
		return (hori_ray_inf);
}
