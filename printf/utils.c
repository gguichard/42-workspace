/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:25:25 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/22 13:40:09 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

char	pad_byte(t_token *tok)
{
	if (tok->flags & MINUS_FLAG)
		return (' ');
	if (tok->flags & ZERO_FLAG)
		return ('0');
	return (' ');
}

void	buf_pad(t_buf *buf, char pad, int width, int right_pad)
{
	char	*tmp;

	if (buf->size >= width)
		return ;
	if (!(tmp = (char *)malloc(width)))
		exit(1);
	if (!right_pad)
	{
		ft_memset(tmp, pad, width - buf->size);
		ft_memcpy(tmp + (width - buf->size), buf->str, buf->size);
	}
	else
	{
		ft_memcpy(tmp, buf->str, buf->size);
		ft_memset(tmp + buf->size, ' ', width - buf->size);
	}
	free(buf->str);
	buf->str = tmp;
	buf->size = width;
}

void	buf_prepend(char *s1, t_buf *buf)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(s1, buf->str)))
		exit(1);
	free(buf->str);
	buf->str = tmp;
	buf->size += ft_strlen(s1);
}
