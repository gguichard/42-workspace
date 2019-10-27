/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:18:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/27 21:19:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ray_inf.h"
#include "map_inf.h"
#include "vec2.h"

t_ray_inf	launch_ray(t_vec2d origin, double angle, t_map_inf *map_inf)
{
	t_ray_inf	ray_inf;

	(void)origin;
	(void)angle;
	(void)map_inf;
	ft_memset(&ray_inf, 0, sizeof(t_ray_inf));
	return (ray_inf);
}
