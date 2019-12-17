/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_ray_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:48:12 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/17 18:31:56 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "wolf3d.h"
#include "ray_inf.h"
#include "vec2.h"

void	init_ray_inf(t_ray_inf *ray_inf, t_vec2d origin, double angle)
{
	ft_memset(ray_inf, 0, sizeof(t_ray_inf));
	ray_inf->origin = origin;
	ray_inf->angle = angle;
	ray_inf->length = INFINITY;
}

int		is_ray_final_hit(t_ray_inf *ray_inf)
{
	return (ray_inf->tile == NULL
		|| ray_inf->tile->type != PORTAL_DATA
		|| ray_inf->tile->data.portal.dir != ray_inf->direction
		|| ray_inf->tile->data.portal.target == NULL);
}

void	free_ray_list(t_ray_list *ray_list)
{
	t_ray_list	*ray_list_prev;

	while (ray_list != NULL)
	{
		ray_list_prev = ray_list->prev;
		free(ray_list);
		ray_list = ray_list_prev;
	}
}
