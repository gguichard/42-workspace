/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 13:58:54 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/21 15:45:28 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include <stdlib.h>
#include "printf.h"
#include "libft.h"

static int		convert_utf8(char *str, wint_t c)
{
	int	index;

	index = 0;
	if (!(c >> 7))
		str[index++] = c;
	else if (c < 0x800)
	{
		str[index++] = (c >> 6) | 0xC0;
		str[index++] = (c & 0x3F) | 0x80;
	}
	else if (c < 0x10000)
	{
		str[index++] = (c >> 12) | 0xE0;
		str[index++] = ((c >> 6) & 0x3F) | 0x80;
		str[index++] = (c & 0x3F) | 0x80;
	}
	else
	{
		str[index++] = (c >> 18) | 0xF0;
		str[index++] = ((c >> 12) & 0x3F) | 0x80;
		str[index++] = ((c >> 6) & 0x3F) | 0x80;
		str[index++] = (c & 0x3F) | 0x80;
	}
	return (index);
}

static size_t	convert_utf8_str(t_buf *buf, wchar_t *str)
{
	size_t	len;
	size_t	bytes;
	size_t	offset;

	len = 0;
	bytes = 0;
	while (str[len] != L'\0')
	{
		if (!(str[len] >> 7))
			bytes += 1;
		else if (str[len] < 0x800)
			bytes += 2;
		else if (str[len] < 0x10000)
			bytes += 3;
		else
			bytes += 4;
		len++;
	}
	if (!(buf->str = (char *)malloc(sizeof(char) * bytes)))
		exit(1);
	len = 0;
	offset = 0;
	while (str[len] != L'\0')
	{
		offset += convert_utf8(&((buf->str)[offset]), str[len]);
		len++;
	}
	return (offset);
}

void			convert_str(t_token *token, va_list ap, t_buf *buf)
{
	char	*str;

	str = va_arg(ap, char *);
	if (str != NULL && token->modifiers & L_MODIFIER)
		buf->size = convert_utf8_str(buf, (wchar_t *)str);
	else
	{
		if (!(buf->str = ft_strdup(!str ? "(null)" : str)))
			exit(1);
		buf->size = ft_strlen(buf->str);
	}
	if (token->precision >= 0 && buf->size > (size_t)token->precision)
	{
		(buf->str)[token->precision] = '\0';
		buf->size = token->precision;
	}
	if (token->width_field > 0)
		buf_pad(buf, padding_byte(token)
			, token->width_field, token->flags & MINUS_FLAG);
}

void			convert_char(t_token *token, va_list ap, t_buf *buf)
{
	if (!(buf->str = (char *)malloc(token->modifiers & L_MODIFIER ? 4 : 1)))
		exit(1);
	if (token->modifiers & L_MODIFIER)
		buf->size = convert_utf8(buf->str, va_arg(ap, wint_t));
	else
	{
		(buf->str)[0] = (char)va_arg(ap, int);
		buf->size = 1;
	}
	if (token->width_field > 0)
		buf_pad(buf, padding_byte(token)
			, token->width_field, token->flags & MINUS_FLAG);
}
