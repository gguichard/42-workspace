/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:18:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/17 19:15:40 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf3d.h"
#include "ray_inf.h"
#include "map_inf.h"
#include "tile_inf.h"
#include "vec2.h"
#include "direction.h"

static t_tile_meta	*get_map_tile(int x, int y, t_map_inf *map_inf)
{
	if (x < 0 || x >= map_inf->width || y < 0 || y >= map_inf->height)
		return (NULL);
	else
		return (&map_inf->tiles[y * map_inf->width + x]);
}

static void			launch_hray(t_ray_inf *ray_inf, t_vec2d dir, double slope
	, t_map_inf *map_inf)
{
	t_vec2d		pos;
	t_tile_meta	*tile;
	double		dumb;

	pos.x = floor(ray_inf->origin.x + (dir.x > 0 ? 1 : 0));
	pos.y = ray_inf->origin.y + fabs(pos.x - ray_inf->origin.x) * slope;
	while (1)
	{
		tile = get_map_tile(pos.x + (dir.x > 0 ? 0 : -1), pos.y, map_inf);
		if (tile == NULL || tile->id != TILE_EMPTY)
			break ;
		pos.x += (dir.x > 0 ? 1 : -1);
		pos.y += slope;
	}
	ray_inf->position = modf(pos.y, &dumb);
	if (ray_inf->position < 0)
		ray_inf->position += 1;
	ray_inf->direction = (dir.x > 0 ? NORTH : SOUTH);
	ray_inf->tile = tile;
	ray_inf->length = sqrt(pow(pos.x - ray_inf->origin.x, 2)
			+ pow(pos.y - ray_inf->origin.y, 2));
}

static void			launch_vray(t_ray_inf *ray_inf, t_vec2d dir, double slope
	, t_map_inf *map_inf)
{
	t_vec2d		pos;
	t_tile_meta	*tile;
	double		dumb;

	pos.y = floor(ray_inf->origin.y + (dir.y > 0 ? 1 : 0));
	pos.x = ray_inf->origin.x + fabs(pos.y - ray_inf->origin.y) * slope;
	while (1)
	{
		tile = get_map_tile(pos.x, pos.y + (dir.y > 0 ? 0 : -1), map_inf);
		if (tile == NULL || tile->id != TILE_EMPTY)
			break ;
		pos.y += (dir.y > 0 ? 1 : -1);
		pos.x += slope;
	}
	ray_inf->position = modf(pos.x, &dumb);
	if (ray_inf->position < 0)
		ray_inf->position += 1;
	ray_inf->direction = (dir.y > 0 ? WEST : EAST);
	ray_inf->tile = tile;
	ray_inf->length = sqrt(pow(pos.x - ray_inf->origin.x, 2)
		+ pow(pos.y - ray_inf->origin.y, 2));
}

static t_ray_list	*launch_new_ray(t_vec2d origin, double angle
	, t_map_inf *map_inf)
{
	t_ray_list	*hit;
	t_vec2d		dir;
	t_ray_inf	hori_ray_inf;
	t_ray_inf	vert_ray_inf;

	hit = (t_ray_list *)malloc(sizeof(t_ray_list));
	if (hit == NULL)
		return (NULL);
	dir = vec2d(cos(angle), -sin(angle));
	init_ray_inf(&vert_ray_inf, origin, angle);
	init_ray_inf(&hori_ray_inf, origin, angle);
	if (fabs(dir.x) != 0.0)
		launch_hray(&hori_ray_inf, dir, dir.y / fabs(dir.x), map_inf);
	if (fabs(dir.y) != 0.0)
		launch_vray(&vert_ray_inf, dir, dir.x / fabs(dir.y), map_inf);
	if (vert_ray_inf.length < hori_ray_inf.length)
		hit->ray_inf = vert_ray_inf;
	else
		hit->ray_inf = hori_ray_inf;
	return (hit);
}

t_ray_list			*launch_ray(t_vec2d origin, double angle, t_map_inf *map_inf
	, int max_depth)
{
	t_ray_list	*last_hit_node;
	t_ray_list	*hit_node;
	t_ray_inf	*ray_inf;

	last_hit_node = NULL;
	while (max_depth > 0)
	{
		hit_node = launch_new_ray(origin, angle, map_inf);
		if (hit_node == NULL)
			break ;
		ray_inf = &hit_node->ray_inf;
		if (last_hit_node != NULL)
			ray_inf->length += last_hit_node->ray_inf.length;
		hit_node->prev = last_hit_node;
		last_hit_node = hit_node;
		if (is_ray_final_hit(ray_inf))
			break ;
		origin = get_portal_launch_origin(ray_inf->direction, ray_inf->position
			, ray_inf->tile->data.portal.target);
		angle += get_portal_angle_diff(&ray_inf->tile->data.portal
				, &ray_inf->tile->data.portal.target->data.portal);
		max_depth--;
	}
	return (last_hit_node);
}
