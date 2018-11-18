/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 22:57:10 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/18 17:00:13 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

void	convert_str(t_token *token, va_list ap, t_buf *buf)
{
	buf->str = va_arg(ap, char *);
	if (!(buf->str = ft_strdup(!(buf->str) ? "(null)" : buf->str)))
		exit(1);
	buf->size = ft_strlen(src);
	if (holder->precision >= 0 && buf->size > (size_t)holder->precision)
	{
		(buf->str)[holder->precision] = '\0';
		buf->size = holder->precision;
	}
	if (holder->width_field > 0)
	{
		buf->str = pad_string(buf->str, padding_byte(holder)
			, holder->width_field, holder->flags & MINUS_FLAG);
		buf->size = holder->width_field;
	}
}

void	convert_char(t_token *token, va_list ap, t_buf *buf)
{
	if (!(buf->str = ft_strndup(va_arg(ap, char), 1)))
		exit(1);
	buf->size = 1;
	if (holder->width_field > 0)
	{
		buf->str = pad_string(buf->str, padding_byte(holder)
			, holder->width_field, holder->flags & MINUS_FLAG);
		buf->size = holder->width_field;
	}
}

void	convert_decimal(t_token *token, va_list ap, t_buf *buf)
{
	if (!(buf->str = decimal_from_type(holder, ap)))
		exit(1);
	buf->size = ft_strlen(buf->str);
	if (holder->type == 'x')
		buf->str = ft_strtolower(buf->str);
	if (holder->precision > 0 && buf->size < holder->precision)
	{
		buf->str = pad_string(buf->str, '0', holder->precision, 0);
		buf->size = holder->precision;
	}
	if ((holder->type == 'd' || holder->type == 'i') && (buf->str)[0] != '-')
	{
		if (holder->flags & PLUS_FLAG)
			buf->str = str_prepend("+", buf->str);
		else if (holder->flags & SPACE_FLAG)
			buf->str = str_prepend(" ", buf->str);
		if (str == NULL)
			exit(1);
	}
	if (str[0] != '0' && holder->flags & HASH_FLAG)
	{
		if (holder->type == 'o')
			str = str_prepend("0", str);
		else if (holder->type == 'x')
			str = str_prepend("0x", str);
		else if (holder->type == 'X')
			str = str_prepend("0X", str);
		if (str == NULL)
			return (NULL);
	}
	if (holder->width_field > 0)
		str = pad_string(str
			, (holder->precision > 0 ? ' ' : padding_byte(holder))
			, holder->width_field, holder->flags & MINUS_FLAG);
	return (str);
}

char	*convert_pointer(t_pholder *holder, va_list ap)
{
	char	*str;

	if (!(str = ft_lltoa_base(va_arg(args, t_intptr), 16)))
		return (NULL);
	str = ft_strtolower(str);
	if (!(str = str_prepend("0x", str)))
		return (NULL);
	if (holder->width_field > 0)
		str = pad_string(str
			, padding_byte(holder)
			, holder->width_field
			, holder->flags & MINUS_FLAG);
	return (str);
}
