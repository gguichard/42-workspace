/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 18:49:05 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/05 19:05:46 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(char *src)
{
	int		size;
	char	*dest;
	int		i;

	size = ft_strlen(src);
	if (!(dest = (char *)malloc(sizeof(*src) * size)))
		return (NULL);
	i = 0;
	while (i <= size)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
