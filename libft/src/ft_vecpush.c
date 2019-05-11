/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:19:26 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 21:09:22 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_vecpush(t_vector *vector, void *elem)
{
	size_t	new_capacity;
	void	**new_data;

	if (vector == NULL)
		return (0);
	else if (vector->size == vector->capacity)
	{
		new_capacity = (vector->capacity == 0 ? 1024 : vector->capacity * 2);
		if (new_capacity < vector->capacity)
			return (0);
		new_data = (void **)malloc(sizeof(void *) * new_capacity);
		if (new_data == NULL)
			return (0);
		if (vector->data != NULL)
		{
			ft_memcpy(new_data, vector->data
				, sizeof(void *) * vector->capacity);
			free(vector->data);
		}
		vector->data = new_data;
		vector->capacity = new_capacity;
	}
	vector->data[vector->size] = elem;
	vector->size += 1;
	return (1);
}
