/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 13:58:54 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/22 10:55:36 by gguichar         ###   ########.fr       */
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
		if (*str < (1 << 7))
			buf->size += 1;
		else if (*str < (1 << 11))
			buf->size += 2;
		else if (*str < (1 << 16))
			buf->size += 3;
		else
			buf->size += 4;
		str++;
	}
}

void		convert_str(t_token *tok, va_list ap)
{
	char	*str;

	str = va_arg(ap, char *);
	if (str == NULL || !(tok->modifiers & L_MODIFIER))
	{
		if (!(tok->buf.str = ft_strdup(!str ? "(null)" : str)))
			exit(1);
		tok->buf.size = ft_strlen(tok->buf.str);
	}
	else
	{
		buf_size(&(tok->buf), (wchar_t *)str);
		if (!(tok->buf.str = (char *)malloc(sizeof(char) * tok->buf.size)))
			exit(1);
		if (!(convert_utf8_str(tok->buf.str, (wchar_t *)str)))
		{
			tok->buf.size = -1;
			return ;
		}
	}
	if (tok->precision >= 0 && tok->buf.size > tok->precision)
		tok->buf.size = tok->precision;
	if (tok->width_field > 0 && tok->buf.size < tok->width_field)
		buf_pad(&(tok->buf), pad_byte(tok), tok->width_field
			, tok->flags & MINUS_FLAG);
}

void		convert_char(t_token *tok, va_list ap)
{
	wint_t	c;

	if (!(tok->buf.str = (char *)malloc((tok->modifiers & L_MODIFIER) ? 4 : 1)))
		exit(1);
	if (!(tok->modifiers & L_MODIFIER))
	{
		(tok->buf.str)[0] = (char)va_arg(ap, int);
		tok->buf.size = 1;
	}
	else
	{
		c = va_arg(ap, wint_t);
		tok->buf.size = convert_utf8(tok->buf.str, c);
		if (!utf8_valid(c))
		{
			tok->buf.size = -1;
			return ;
		}
	}
	if (tok->width_field > 0 && tok->buf.size < tok->width_field)
		buf_pad(&(tok->buf), pad_byte(tok), tok->width_field
			, tok->flags & MINUS_FLAG);
}
