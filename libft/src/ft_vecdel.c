/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:27:18 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/24 22:23:41 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_vecdel(t_vector *vector, void (*f)(void *))
{
	size_t	index;

	if (vector != NULL)
	{
		index = 0;
		while (index < vector->size)
		{
			f(vector->data[index]);
			index++;
		}
		ft_memset(vector, 0, sizeof(t_vector));
	}
}
