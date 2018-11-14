/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:25:25 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/14 22:54:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

static char	padding_byte(t_pholder *holder)
{
	return ((holder->flags & ZERO_FLAG) ? '0' : ' ');
}

char		*pad_string(char *str, t_pholder *holder)
{
	size_t	len;
	char	*ret;

	ret = str;
	len = ft_strlen(str);
	if ((size_t)holder->width_field > len)
	{
		if (!(ret = (char *)malloc(holder->width_field + 1)))
			return (NULL);
		free(str);
		ft_memset(ret, padding_byte(holder), holder->width_field - len);
		ft_memcpy(ret + (holder->width_field - len), str, len + 1);
	}
	return (ret);
}
