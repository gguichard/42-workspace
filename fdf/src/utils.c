/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 05:08:55 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/30 18:33:21 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "fdf.h"

int		window_size(const char *str)
{
	int	size;

	if (str == NULL)
		return (-1);
	size = ft_atoi(str);
	if (size <= 0 || size > 2560)
		return (-1);
	return (size);
}

int		exit_fdf(t_fdf *fdf)
{
	clean_mlx(fdf);
	exit(0);
	return (0);
}

void	draw_pixel(t_fdf *fdf, int x, int y, int color)
{
	if (y >= 0 && x >= 0 && y < fdf->height && x < fdf->width)
		fdf->lib.img_data[y * fdf->width + x] = color;
}

void	draw_line(t_fdf *fdf, t_pos pos1, t_pos pos2, int color)
{
	t_pos	delta;
	t_pos	step;
	int		err;
	int		tmp;

	delta.x = ft_abs(pos2.x - pos1.x);
	delta.y = -ft_abs(pos2.y - pos1.y);
	step.x = pos1.x < pos2.x ? 1 : -1;
	step.y = pos1.y < pos2.y ? 1 : -1;
	err = delta.x + delta.y;
	while (pos1.x != pos2.x || pos1.y != pos2.y)
	{
		draw_pixel(fdf, pos1.x, pos1.y, color);
		tmp = 2 * err;
		if (tmp >= delta.y)
		{
			err += delta.y;
			pos1.x += step.x;
		}
		if (tmp <= delta.x)
		{
			err += delta.x;
			pos1.y += step.y;
		}
	}
}
