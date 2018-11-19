/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:25:25 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/19 14:03:39 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

char	padding_byte(t_token *token)
{
	if (token->flags & MINUS_FLAG)
		return (' ');
	if (token->flags & ZERO_FLAG)
		return ('0');
	return (' ');
}

void	buf_pad(t_buf *buf, char pad, int width, int right_pad)
{
	char	*tmp;

	if ((size_t)width <= buf->size)
		return ;
	tmp = buf->str;
	if (!(buf->str = (char *)malloc(width + 1)))
		return ;
	if (!right_pad)
	{
		ft_memset(buf->str, pad, width - buf->size);
		ft_memcpy(buf->str + (width - buf->size), tmp, buf->size + 1);
	}
	else
	{
		ft_memcpy(buf->str, tmp, buf->size);
		ft_memset(buf->str + buf->size, ' ', width - buf->size);
		(buf->str)[width] = '\0';
	}
	buf->size = width;
	free(tmp);
}

void	buf_prepend(char *s1, t_buf *buf)
{
	char	*tmp;

	tmp = buf->str;
	buf->str = ft_strjoin(s1, buf->str);
	buf->size = ft_strlen(buf->str);
	free(tmp);
}
