/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 01:07:39 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/31 01:42:25 by gguichar         ###   ########.fr       */
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

static int		get_color(t_pos pos1, t_pos pos2, t_pos curr, t_pos delta)
{
	int		r;
	int		g;
	int		b;
	double	ratio;

	if (delta.x > delta.y)
		ratio = get_ratio(pos1.x, pos2.x, curr.x);
	else
		ratio = get_ratio(pos1.y, pos2.y, curr.y);
	r = get_light((pos1.color >> 16) & 0xFF, (pos2.color >> 16) & 0xFF, ratio);
	g = get_light((pos1.color >> 8) & 0xFF, (pos2.color >> 8) & 0xFF, ratio);
	b = get_light(pos1.color & 0xFF, pos2.color & 0xFF, ratio);
	return ((r << 16) | (g << 8) | b);
}

void			draw_pixel(t_fdf *fdf, t_pos pos1, t_pos pos2, t_pos curr)
{
	t_pos	delta;
	int		color;

	if (curr.x >= 0 && curr.y >= 0
			&& curr.x < fdf->width && curr.y < fdf->height)
	{
		delta.x = ft_abs(pos2.x - pos1.x);
		delta.y = ft_abs(pos2.y - pos1.y);
		color = get_color(pos1, pos2, curr, delta);
		fdf->lib.img_data[curr.y * fdf->width + curr.x] = color;
	}
}

void			draw_line(t_fdf *fdf, t_pos pos1, t_pos pos2)
{
	t_pos	delta;
	t_pos	step;
	t_pos	curr;
	int		err;
	int		tmp;

	delta.x = ft_abs(pos2.x - pos1.x);
	delta.y = ft_abs(pos2.y - pos1.y);
	step.x = pos1.x < pos2.x ? 1 : -1;
	step.y = pos1.y < pos2.y ? 1 : -1;
	curr.x = pos1.x;
	curr.y = pos1.y;
	err = delta.x - delta.y;
	while (curr.x != pos2.x || curr.y != pos2.y)
	{
		draw_pixel(fdf, pos1, pos2, curr);
		tmp = 2 * err;
		(tmp >= -(delta.y)) ? err -= delta.y : 0;
		(tmp >= -(delta.y)) ? curr.x += step.x : 0;
		(tmp <= delta.x) ? err += delta.x : 0;
		(tmp <= delta.x) ? curr.y += step.y : 0;
	}
}
