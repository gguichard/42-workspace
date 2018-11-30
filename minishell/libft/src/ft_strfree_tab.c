/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfree_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 10:03:47 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/30 10:06:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_strfree_tab(char **tab)
{
	size_t	index;

	if (tab == NULL)
		return (NULL);
	index = 0;
	while (tab[index] != NULL)
	{
		free(tab[index]);
		index++;
	}
	free(tab);
	return (NULL);
}
