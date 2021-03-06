/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 09:04:02 by wta               #+#    #+#             */
/*   Updated: 2018/11/17 13:40:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "fillit.h"

static int		init_shape(t_shape **shape)
{
	if (!(*shape = (t_shape *)malloc(sizeof(t_shape))))
		return (0);
	(*shape)->data = 0;
	(*shape)->width = 0;
	(*shape)->height = 0;
	(*shape)->pos.x = -1;
	(*shape)->pos.y = -1;
	(*shape)->x_min = 10;
	(*shape)->x_max = -1;
	return (1);
}

static char		build_mask(t_shape *shape, char buf[5])
{
	int				i;
	unsigned char	mask;

	i = 0;
	mask = 0;
	while (i < 4)
	{
		mask |= (buf[i] & 1) << (3 - i);
		if (buf[i] & 1)
		{
			if (i < shape->x_min)
				shape->x_min = i;
			if (i > shape->x_max)
				shape->x_max = i;
		}
		i++;
	}
	return (mask);
}

static t_ushort	shift_unused_bits(t_ushort data)
{
	unsigned char	mask;
	int				row;
	t_ushort		tmp;

	while (data && data < 0x1000)
		data <<= 4;
	while (data)
	{
		row = 0;
		tmp = data;
		while (row < 4)
		{
			mask = tmp >> 12;
			if (mask >= 8)
				return (data);
			tmp <<= 4;
			row++;
		}
		data <<= 1;
	}
	return (data);
}

static int		build_shape(const int fd, t_shape **shape, char buf[5])
{
	unsigned char	mask;
	t_ushort		data;
	int				row;
	int				size_read;

	if (!init_shape(shape))
		return (0);
	data = 0;
	row = 0;
	while (row < 4 && (row == 0 || (size_read = read(fd, buf, 5)) > 0))
	{
		if (!check_line(buf))
			return (0);
		mask = build_mask(*shape, buf);
		if (mask > 0)
			(*shape)->height++;
		data |= mask << (3 - row) * 4;
		row++;
	}
	(*shape)->width = (*shape)->x_max - (*shape)->x_min + 1;
	(*shape)->data = shift_unused_bits(data);
	if ((size_read <= 0 && row != 4) || !is_shape_valid(*shape))
		return (0);
	return (1);
}

t_shape			**get_shapes(int fd)
{
	t_shape	**shapes;
	int		index;
	char	buf[5];
	int		ret;

	if (!(shapes = (t_shape **)malloc(sizeof(*shapes) * 27)))
		return (NULL);
	index = 0;
	while ((ret = read(fd, buf, 5)) > 0)
	{
		if (index == 26
			|| !build_shape(fd, &(shapes[index]), buf)
			|| read(fd, buf, 1) < 0)
			return (NULL);
		index++;
	}
	if (ret < 0 || index == 0 || buf[0] == '\n')
		return (NULL);
	shapes[index] = NULL;
	return (shapes);
}
