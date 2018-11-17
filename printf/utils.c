/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:25:25 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/16 20:23:47 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

char		padding_byte(t_pholder *holder)
{
	if (holder->flags & MINUS_FLAG)
		return (' ');
	return (holder->flags & ZERO_FLAG ? '0' : ' ');
}

char		*pad_string(char *str, char c, size_t width, int right)
{
	char	*ret;
	size_t	len;

	ret = str;
	len = ft_strlen(str);
	if (width > len)
	{
		if (!(ret = (char *)malloc(width + 1)))
			return (NULL);
		if (!right)
		{
			ft_memset(ret, c, width - len);
			ft_memcpy(ret + (width - len), str, len + 1);
		}
		else
		{
			ft_memcpy(ret, str, len);
			ft_memset(ret + len, ' ', width - len);
			ret[width] = '\0';
		}
		free(str);
	}
	return (ret);
}

int			base_from_type(t_pholder *holder)
{
	if (holder->type == 'o')
		return (8);
	if (holder->type == 'x' || holder->type == 'X')
		return (16);
	return (10);
}

char		*str_prepend(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s2);
	return (res);
}
