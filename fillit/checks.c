/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 22:44:51 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/13 23:37:09 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			check_line(const char *str)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (str[i] != '.' && str[i] != '#')
			return (0);
		i++;
	}
	return (str[i] == '\n');
}

static int	check_colliding_bits(unsigned char byte)
{
	while (!(byte & 1))
		byte >>= 1;
	return (byte == 1 || byte == 3 || byte == 7 || byte == 15);
}

int			is_shape_valid(t_shape *shape)
{
	t_ushort		data;
	unsigned char	byte;
	unsigned char	prev_byte;
	int				active_bits;

	data = shape->data;
	prev_byte = 0;
	active_bits = 0;
	while (data)
	{
		byte = data;
		byte <<= 4;
		byte >>= 4;
		if (byte != 0 && !check_colliding_bits(byte))
			return (0);
		if (byte == 0 && prev_byte != 0 && active_bits < 4)
			return (0);
		if (byte != 0 && prev_byte != 0
			&& (byte ^ prev_byte) == (byte | prev_byte))
			return (0);
		prev_byte = byte;
		active_bits += count_active_bits(byte);
		data >>= 4;
	}
	return (active_bits == 4);
}

int			is_overlapping(t_info *info, t_shape *shape)
{
	int			i;
	t_ushort	row;
	t_ushort	row_board;

	if (shape->pos.x + shape->width > info->size
		|| shape->pos.y + shape->height > info->size)
		return (1);
	i = 0;
	while (i < 4)
	{
		row = (shape->data >> (3 - i) * 4) << 12;
		row_board = info->board[shape->pos.y + i] << shape->pos.x;
		if ((row & row_board) != 0)
			return (1);
		i++;
	}
	return (0);
}
