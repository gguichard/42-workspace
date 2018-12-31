/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 01:07:39 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/31 02:13:06 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static int		get_light(int start, int end, double percent)
{
	return (int)((1 - percent) * start + percent * end);
}

static double	get_ratio(int start, int end, int current)
{
	double	dist;

	dist = end - start;
	if (dist == 0)
		return (1.0);
	return ((current - start) / dist);
}

static int		get_color(t_pos start, t_pos end, t_pos curr, t_pos delta)
{
	int		r;
	int		g;
	int		b;
	double	ratio;

	if (delta.x > delta.y)
		ratio = get_ratio(start.proj_x, end.proj_x, curr.proj_x);
	else
		ratio = get_ratio(start.proj_y, end.proj_y, curr.proj_y);
	r = get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, ratio);
	g = get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, ratio);
	b = get_light(start.color & 0xFF, end.color & 0xFF, ratio);
	return ((r << 16) | (g << 8) | b);
}

void			draw_pixel(t_fdf *fdf, t_pos start, t_pos end, t_pos curr)
{
	t_pos	delta;
	int		color;

	if (curr.proj_x >= 0 && curr.proj_y >= 0
			&& curr.proj_x < fdf->width && curr.proj_y < fdf->height)
	{
		if (start.color == end.color)
			color = start.color;
		else
		{
			delta.x = ft_abs(end.proj_x - start.proj_x);
			delta.y = ft_abs(end.proj_y - start.proj_y);
			color = get_color(start, end, curr, delta);
		}
		fdf->lib.img_data[curr.proj_y * fdf->width + curr.proj_x] = color;
	}
}

void			draw_line(t_fdf *fdf, t_pos start, t_pos end)
{
	t_pos	delta;
	t_pos	step;
	t_pos	curr;
	int		err;
	int		tmp;

	delta.x = ft_abs(end.proj_x - start.proj_x);
	delta.y = ft_abs(end.proj_y - start.proj_y);
	step.x = start.proj_x < end.proj_x ? 1 : -1;
	step.y = start.proj_y < end.proj_y ? 1 : -1;
	curr.proj_x = start.proj_x;
	curr.proj_y = start.proj_y;
	err = delta.x - delta.y;
	while (curr.proj_x != end.proj_x || curr.proj_y != end.proj_y)
	{
		draw_pixel(fdf, start, end, curr);
		tmp = 2 * err;
		(tmp >= -(delta.y)) ? err -= delta.y : 0;
		(tmp >= -(delta.y)) ? curr.proj_x += step.x : 0;
		(tmp <= delta.x) ? err += delta.x : 0;
		(tmp <= delta.x) ? curr.proj_y += step.y : 0;
	}
}
