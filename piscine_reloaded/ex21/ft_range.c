/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 19:07:19 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/05 19:23:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	*tab;
	int	i;

	if (min >= max)
		return (NULL);
	if (!(tab = (int *)malloc(sizeof(*tab) * (max - min))))
		return (NULL);
	i = 0;
	while (min < max)
	{
		tab[i] = min++;
		i++;
	}
	return (tab);
}
