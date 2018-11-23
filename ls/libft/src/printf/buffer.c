/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 08:27:55 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/22 13:50:02 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "printf.h"

static void	buf_append(t_buf *buf, const char *str, int size)
{
	while (buf->offset + size > buf->size)
		expand_buf(buf);
	if (size > 0)
		ft_memcpy(buf->str + buf->offset, str, size);
	buf->offset += size;
}

static void	buf_init(t_buf *buf)
{
	buf->str = NULL;
	buf->size = 0;
	buf->offset = 0;
}

void		expand_buf(t_buf *buf)
{
	char	*tmp;

	if (!(tmp = (char *)malloc(buf->size + PRINTF_BUF)))
		exit(1);
	if (buf->str != NULL)
	{
		ft_memcpy(tmp, buf->str, buf->size);
		free(buf->str);
	}
	buf->str = tmp;
	buf->size += PRINTF_BUF;
}

int			fill_buf(t_buf *buf, const char *str, va_list ap)
{
	const char	*start;
	t_token		tok;

	buf_init(buf);
	while ((start = ft_strchr(str, '%')) != NULL)
	{
		if (start > str)
			buf_append(buf, str, (int)(start - str));
		start += tok_parse(&tok, start + 1) + 1;
		if (tok.type == 0)
			return (1);
		str = start + 1;
		buf_init(&(tok.buf));
		pf_convert(&tok, ap);
		if (tok.buf.size > 0)
			buf_append(buf, tok.buf.str, tok.buf.size);
		if (tok.buf.str != NULL)
			free(tok.buf.str);
		if (tok.buf.size < 0)
			return (-1);
	}
	if (*str != '\0')
		buf_append(buf, str, ft_strlen(str));
	return (1);
}
