/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_veciter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:24:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/24 16:26:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_veciter(t_vector *vector, void (*f)(size_t, void *))
{
	size_t	index;

	index = 0;
	while (index < vector->size)
	{
		f(index, vector->data[index]);
		index++;
	}
}
