/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:11:09 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/13 23:41:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "limits.h"

static void	place_shape(t_info *info, t_shape *shape)
{
	int			i;
	t_ushort	row;

	i = 0;
	while (i < 4)
	{
		row = (shape->data >> (3 - i) * 4) << 12;
		info->board[shape->pos.y + i] ^= (row >> shape->pos.x);
		i++;
	}
}

static int	move_shape(t_info *info, t_shape *curr)
{
	curr->pos.x++;
	if (curr->pos.x + curr->width > info->size)
	{
		curr->pos.x = 0;
		curr->pos.y++;
		if (curr->pos.y + curr->height > info->size)
		{
			curr->pos.x = -1;
			curr->pos.y = -1;
			return (0);
		}
	}
	return (1);
}

int			solve(t_info *info, int index)
{
	t_shape	*curr;

	curr = info->shapes[index];
	if (curr == NULL)
		return (1);
	curr->pos.x = -1;
	curr->pos.y = 0;
	while (move_shape(info, curr))
	{
		if (!is_overlapping(info, curr))
		{
			place_shape(info, curr);
			if (solve(info, index + 1))
				return (1);
			place_shape(info, curr);
		}
	}
	return (0);
}

void		resolve(t_info *info)
{
	while (!solve(info, 0))
		info->size++;
	print_shapes(info);
}
