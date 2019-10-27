/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_inf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:10:14 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/27 21:31:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_INF_H
# define RAY_INF_H

# include "direction.h"
# include "tile_inf.h"

typedef struct	s_ray_inf
{
	t_direction	direction;
	double		position;
	double		length;
	t_tile_id	tile_id;
}				t_ray_inf;

#endif
