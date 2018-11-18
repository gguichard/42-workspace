/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:25:25 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/18 22:02:55 by gguichar         ###   ########.fr       */
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

int		base_from_type(t_token *token)
{
	if (token->type == 'o')
		return (8);
	if (token->type == 'x' || token->type == 'X')
		return (16);
	return (10);
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
	buf->size += ft_strlen(s1);
	free(tmp);
}
