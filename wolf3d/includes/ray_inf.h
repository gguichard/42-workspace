/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_inf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:10:14 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/31 11:02:23 by gguichar         ###   ########.fr       */
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
	double		position;
	t_direction	direction;
	t_tile_id	tile_id;
	double		length;
}				t_ray_inf;

#endif
