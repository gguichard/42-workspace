/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 01:07:39 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/22 19:29:18 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "line_draw.h"

static inline void	draw_pixel(t_fdf *fdf, t_line line)
{
	double	percent;
	int		index;

	if (line.dx > line.dy)
		percent = pcnt(line.x0, line.x1, line.x);
	else
		percent = pcnt(line.y0, line.y1, line.y);
	line.z = lint(line.z0, line.z1, percent);
	index = line.y * fdf->winsize.width + line.x;
	if ((fdf->z_buffer)[index] >= line.z)
		return ;
	(fdf->z_buffer)[index] = line.z;
	fdf->lib.img_data[index] = get_color(line.c0, line.c1, percent);
}

static inline void	step_line(t_line *line)
{
	int	tmp;

	tmp = 2 * line->err;
	if (tmp >= -line->dy)
	{
		line->err -= line->dy;
		line->x += line->sx;
	}
	if (tmp <= line->dx)
	{
		line->err += line->dx;
		line->y += line->sy;
	}
}

static inline void	draw_line_bresenham(t_fdf *fdf, t_pos start, t_pos end)
{
	t_line	line;

	line.x0 = (int)start.proj.x;
	line.y0 = (int)start.proj.y;
	line.z0 = start.z;
	line.c0 = start.color;
	line.x1 = (int)end.proj.x;
	line.y1 = (int)end.proj.y;
	line.z1 = end.z;
	line.c1 = end.color;
	line.dx = ft_abs(line.x1 - line.x0);
	line.dy = ft_abs(line.y1 - line.y0);
	line.sx = line.x0 < line.x1 ? 1 : -1;
	line.sy = line.y0 < line.y1 ? 1 : -1;
	line.x = line.x0;
	line.y = line.y0;
	line.err = line.dx - line.dy;
	while (line.x != line.x1 || line.y != line.y1)
	{
		if (line.x >= 0 && line.y >= 0
			&& line.x < fdf->winsize.width && line.y < fdf->winsize.height)
			draw_pixel(fdf, line);
		step_line(&line);
	}
}

void				draw_line(t_fdf *fdf, t_pos start, t_pos end)
{
	if ((start.proj.x < 0 && end.proj.x < 0)
		|| (start.proj.y < 0 && end.proj.y < 0)
		|| (start.proj.x >= fdf->winsize.width
			&& end.proj.x >= fdf->winsize.width)
		|| (start.proj.y >= fdf->winsize.height
			&& end.proj.y >= fdf->winsize.height))
		return ;
	draw_line_bresenham(fdf, start, end);
}
