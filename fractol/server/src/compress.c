/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 22:23:52 by gguichar          #+#    #+#             */
/*   Updated: 2019/03/01 22:40:00 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "fractol.h"

int	*rle_compress(int *buffer, int size, int *new_size)
{
	int	*new_data;
	int	buff_index;
	int	index;

	new_data = (int *)malloc(sizeof(int) * size * 2);
	if (new_data == NULL)
		return (NULL);
	buff_index = 0;
	index = 0;
	while (buff_index < size)
	{
		new_data[index] = 1;
		new_data[index + 1] = buffer[buff_index];
		buff_index++;
		while (buff_index < size && buffer[buff_index] == new_data[index + 1])
		{
			new_data[index] += 1;
			buff_index++;
		}
		index += 2;
	}
	*new_size = index;
	return (new_data);
}
