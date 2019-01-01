/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 01:07:39 by gguichar          #+#    #+#             */
/*   Updated: 2019/01/01 16:22:21 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

void		draw_pixel(t_fdf *fdf, t_pos limits[2], t_pos delta, t_pos curr)
{
	double	percent;
	int		index;

	if (curr.proj_x < 0 || curr.proj_y < 0
			|| curr.proj_x >= fdf->width || curr.proj_y >= fdf->height)
		return ;
	if (delta.x > delta.y)
		percent = pcnt(limits[0].proj_x, limits[1].proj_x, curr.proj_x);
	else
		percent = pcnt(limits[0].proj_y, limits[1].proj_y, curr.proj_y);
	curr.z = lint(limits[0].z, limits[1].z, percent);
	index = curr.proj_y * fdf->width + curr.proj_x;
	if ((fdf->z_buffer)[index] >= curr.z)
		return ;
	(fdf->z_buffer)[index] = curr.z;
	fdf->lib.img_data[index] = get_color(limits[0], limits[1], percent);
}

static void	step_line(int *err, t_pos delta, t_pos step, t_pos *curr)
{
	err[1] = 2 * err[0];
	if (err[1] >= delta.y)
	{
		err[0] += delta.y;
		curr->proj_x += step.x;
	}
	if (err[1] <= delta.x)
	{
		err[0] += delta.x;
		curr->proj_y += step.y;
	}
}

void		draw_line(t_fdf *fdf, t_pos start, t_pos end)
{
	t_pos	limits[2];
	t_pos	delta;
	t_pos	step;
	t_pos	curr;
	int		err[2];

	limits[0] = start;
	limits[1] = end;
	delta.x = ft_abs(end.proj_x - start.proj_x);
	delta.y = -ft_abs(end.proj_y - start.proj_y);
	step.x = start.proj_x < end.proj_x ? 1 : -1;
	step.y = start.proj_y < end.proj_y ? 1 : -1;
	curr.proj_x = start.proj_x;
	curr.proj_y = start.proj_y;
	err[0] = delta.x + delta.y;
	while (curr.proj_x != end.proj_x || curr.proj_y != end.proj_y)
	{
		draw_pixel(fdf, limits, delta, curr);
		step_line(err, delta, step, &curr);
	}
}
