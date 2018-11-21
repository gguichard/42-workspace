/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 13:58:54 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/22 00:00:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

static void	buf_size(t_buf *buf, wchar_t *str)
{
	buf->size = 0;
	while (*str != L'\0')
	{
		if (*str < (1 << 8))
			buf->size += 1;
		else if (*str < (1 << 12))
			buf->size += 2;
		else if (*str < (1 << 16))
			buf->size += 3;
		else
			buf->size += 4;
		str++;
	}
}

void		convert_str(t_token *tok, va_list ap, t_buf *buf)
{
	char	*str;

	str = va_arg(ap, char *);
	if (str == NULL || !(tok->modifiers & L_MODIFIER))
	{
		if (!(buf->str = ft_strdup(!str ? "(null)" : str)))
			exit(1);
		buf->size = ft_strlen(buf->str);
	}
	else
	{
		buf_size(buf, (wchar_t *)str);
		if (!(buf->str = (char *)malloc(sizeof(char) * buf->size)))
			exit(1);
		if (!(convert_utf8_str(buf->str, (wchar_t *)str)))
			exit(1);
	}
	if (tok->precision >= 0 && buf->size > (size_t)tok->precision)
		buf->size = tok->precision;
	if (tok->width_field > 0 && buf->size < (size_t)tok->width_field)
		buf_pad(buf, pad_byte(tok), tok->width_field, tok->flags & MINUS_FLAG);
}

void		convert_char(t_token *tok, va_list ap, t_buf *buf)
{
	wint_t	c;

	if (!(buf->str = (char *)malloc((tok->modifiers & L_MODIFIER) ? 4 : 1)))
		exit(1);
	if (!(tok->modifiers & L_MODIFIER))
	{
		(buf->str)[0] = (char)va_arg(ap, int);
		buf->size = 1;
	}
	else
	{
		c = va_arg(ap, wint_t);
		buf->size = convert_utf8(buf->str, c);
		if (!utf8_valid(c))
			exit(1);
	}
	if (tok->width_field > 0 && buf->size < (size_t)tok->width_field)
		buf_pad(buf, pad_byte(tok), tok->width_field, tok->flags & MINUS_FLAG);
}
