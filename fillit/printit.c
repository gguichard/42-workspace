/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:17:30 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/17 13:36:39 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

static void	print_shape(t_info *info, int x, int y)
{
	int			index;
	t_shape		*shape;
	t_ushort	mask;

	index = 0;
	while ((shape = info->shapes[index]) != NULL)
	{
		if (x >= shape->pos.x && x < shape->pos.x + shape->width
			&& y >= shape->pos.y && y < shape->pos.y + shape->height)
		{
			mask = shape->data;
			mask <<= (y - shape->pos.y) * 4;
			mask <<= (x - shape->pos.x);
			if (mask >= 0x8000)
			{
				ft_putchar('A' + index);
				return ;
			}
		}
		index++;
	}
	ft_putchar('?');
}

void		print_shapes(t_info *info)
{
	int			y;
	int			x;
	t_ushort	row;

	y = 0;
	while (y < info->size)
	{
		x = 0;
		row = info->board[y];
		while (x < info->size)
		{
			if (row < 0x8000)
				ft_putchar('.');
			else
				print_shape(info, x, y);
			row <<= 1;
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}
