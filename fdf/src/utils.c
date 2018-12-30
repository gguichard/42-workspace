/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 05:08:55 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/30 06:48:37 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "fdf.h"

int		exit_fdf(t_fdf *fdf)
{
	clean_mlx(fdf);
	exit(0);
	return (0);
}

void	draw_pixel(t_fdf *fdf, int x, int y)
{
	if (y >= 0 && x >= 0 && y < fdf->height && x < fdf->width)
		fdf->lib.img_data[y * fdf->width + x] = 0xFFFFFF;
}

void	draw_line(t_fdf *fdf, t_pos pos1, t_pos pos2)
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
		draw_pixel(fdf, pos1.x, pos1.y);
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
