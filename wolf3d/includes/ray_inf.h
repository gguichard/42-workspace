/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_inf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:10:14 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/17 17:40:39 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_INF_H
# define RAY_INF_H

# include "vec2.h"
# include "direction.h"
# include "tile_inf.h"

typedef struct	s_ray_inf
{
	t_vec2d		origin;
	double		angle;
	double		position;
	t_direction	direction;
	t_tile_meta	*tile;
	double		length;
}				t_ray_inf;

typedef struct	s_ray_list
{
	t_ray_inf			ray_inf;
	struct s_ray_list	*prev;
}				t_ray_list;

#endif
