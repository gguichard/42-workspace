/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:03:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/01/01 22:24:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "fdf.h"

static void	proj_pos(t_fdf *fdf, t_pos *pos)
{
	t_pos	data;
	int		x;
	int		y;

	x = pos->x - fdf->cols / 2;
	y = pos->y - fdf->rows / 2;
	x *= fdf->cam.scale;
	y *= fdf->cam.scale;
	data.x = x;
	data.y = y;
	x = data.x * fdf->cam.angle_cos - data.y * fdf->cam.angle_sin;
	y = data.y * fdf->cam.angle_cos + data.x * fdf->cam.angle_sin;
	data.x = x;
	data.y = y;
	data.z = pos->z * fdf->cam.depth;
	fdf->f_proj(data, &(pos->proj_x), &(pos->proj_y));
	pos->proj_x += (fdf->width / 2) + fdf->cam.x;
	pos->proj_y += (fdf->height / 2) + fdf->cam.y;
}

static void	rasterize(t_fdf *fdf, t_pos pos, t_pos edge)
{
	if ((pos.proj_x < 0 && edge.proj_x < 0)
			|| (pos.proj_y < 0 && edge.proj_y < 0)
			|| (pos.proj_x >= fdf->width && edge.proj_x >= fdf->width)
			|| (pos.proj_y >= fdf->height && edge.proj_y >= fdf->height))
		return ;
	draw_line(fdf, pos, edge);
}

static void	draw_edges(t_fdf *fdf, t_pos pos)
{
	t_pos	edge;

	if (pos.x + 1 < fdf->cols)
	{
		edge = (fdf->pos)[pos.y * fdf->cols + pos.x + 1];
		rasterize(fdf, pos, edge);
	}
	if (pos.y + 1 < fdf->rows)
	{
		edge = (fdf->pos)[(pos.y + 1) * fdf->cols + pos.x];
		rasterize(fdf, pos, edge);
	}
}

static void	clear_window(t_fdf *fdf)
{
	int	index;
	int	total;

	index = 0;
	total = fdf->width * fdf->height;
	while (index < total)
	{
		(fdf->z_buffer)[index] = INT_MIN;
		index++;
	}
	ft_memset(fdf->lib.img_data, 0, fdf->lib.size_line * fdf->height);
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
