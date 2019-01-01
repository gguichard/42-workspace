/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 01:07:39 by gguichar          #+#    #+#             */
/*   Updated: 2019/01/01 03:56:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

void	draw_pixel(t_fdf *fdf, t_pos start, t_pos end, t_pos curr)
{
	t_pos	delta;
	double	percent;
	int		index;

	if (curr.proj_x < 0 || curr.proj_y < 0
			|| curr.proj_x >= fdf->width || curr.proj_y >= fdf->height)
		return ;
	delta.x = ft_abs(end.proj_x - start.proj_x);
	delta.y = ft_abs(end.proj_y - start.proj_y);
	if (delta.x > delta.y)
		percent = pcnt(start.proj_x, end.proj_x, curr.proj_x);
	else
		percent = pcnt(start.proj_y, end.proj_y, curr.proj_y);
	curr.z = lint(start.z, end.z, percent);
	index = curr.proj_y * fdf->width + curr.proj_x;
	if ((fdf->z_buffer)[index] >= curr.z)
		return ;
	(fdf->z_buffer)[index] = curr.z;
	fdf->lib.img_data[index] = get_color(start, end, percent);
}

void	draw_line(t_fdf *fdf, t_pos start, t_pos end)
{
	t_pos	delta;
	t_pos	step;
	t_pos	curr;
	int		err;
	int		tmp;

	delta.x = ft_abs(end.proj_x - start.proj_x);
	delta.y = -ft_abs(end.proj_y - start.proj_y);
	step.x = start.proj_x < end.proj_x ? 1 : -1;
	step.y = start.proj_y < end.proj_y ? 1 : -1;
	curr.proj_x = start.proj_x;
	curr.proj_y = start.proj_y;
	err = delta.x + delta.y;
	while (curr.proj_x != end.proj_x || curr.proj_y != end.proj_y)
	{
		draw_pixel(fdf, start, end, curr);
		tmp = 2 * err;
		(tmp >= delta.y) ? err += delta.y : 0;
		(tmp >= delta.y) ? curr.proj_x += step.x : 0;
		(tmp <= delta.x) ? err += delta.x : 0;
		(tmp <= delta.x) ? curr.proj_y += step.y : 0;
	}
}
