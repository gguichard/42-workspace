/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:03:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/31 19:04:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "fdf.h"
#include "bresenham.h"

static void	proj_pos(t_fdf *fdf, t_pos *pos)
{
	t_pos	data;
	int		x;
	int		y;

	x = pos->x - fdf->cols / 2;
	y = pos->y - fdf->rows / 2;
	x *= fdf->cam.scale;
	y *= fdf->cam.scale;
	data.x = x * fdf->cam.angle_cos - y * fdf->cam.angle_sin;
	data.y = y * fdf->cam.angle_cos + x * fdf->cam.angle_sin;
	data.z = pos->z * fdf->cam.scale * fdf->cam.depth;
	fdf->fn_proj(data, &(pos->proj_x), &(pos->proj_y));
	pos->proj_x += fdf->winsize.width / 2;
	pos->proj_y += fdf->winsize.height / 2;
	pos->proj_x += fdf->cam.x * fdf->cam.scale;
	pos->proj_y += fdf->cam.y * fdf->cam.scale;
}

static void	rasterize(t_fdf *fdf, t_pos pos, t_pos edge)
{
	if ((pos.proj_x < 0 && edge.proj_x < 0)
		|| (pos.proj_y < 0 && edge.proj_y < 0)
		|| (pos.proj_x >= fdf->winsize.width
			&& edge.proj_x >= fdf->winsize.width)
		|| (pos.proj_y >= fdf->winsize.height
			&& edge.proj_y >= fdf->winsize.height))
		return ;
	draw_line(fdf, pos, edge);
}

static void	draw_edges(t_fdf *fdf, t_pos pos)
{
	if (pos.x + 1 < fdf->cols)
		rasterize(fdf, pos, (fdf->pos)[pos.y * fdf->cols + pos.x + 1]);
	if (pos.y + 1 < fdf->rows)
		rasterize(fdf, pos, (fdf->pos)[(pos.y + 1) * fdf->cols + pos.x]);
}

static void	clear_window(t_fdf *fdf)
{
	int	index;
	int	total;

	index = 0;
	total = fdf->winsize.width * fdf->winsize.height;
	while (index < total)
	{
		(fdf->z_buffer)[index] = INT_MIN;
		index++;
	}
	ft_memset(fdf->lib.img_data, 0, fdf->lib.size_line * fdf->winsize.height);
}

void		fill_window_image(t_fdf *fdf)
{
	int	index;
	int	total;

	clear_window(fdf);
	total = fdf->rows * fdf->cols;
	index = 0;
	while (index < total)
	{
		proj_pos(fdf, &((fdf->pos)[index]));
		index++;
	}
	index = 0;
	while (index < total)
	{
		draw_edges(fdf, (fdf->pos)[index]);
		index++;
	}
}
