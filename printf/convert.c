/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 22:57:10 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/18 23:38:42 by gguichar         ###   ########.fr       */
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
	buf->size = ft_strlen(buf->str);
	if (token->precision >= 0 && buf->size > (size_t)token->precision)
	{
		(buf->str)[token->precision] = '\0';
		buf->size = token->precision;
	}
	if (token->width_field > 0)
		buf_pad(buf, padding_byte(token)
			, token->width_field, token->flags & MINUS_FLAG);
}

void	convert_char(t_token *token, va_list ap, t_buf *buf)
{
	if (!(buf->str = (char *)malloc(1)))
		exit(1);
	(buf->str)[0] = (char)va_arg(ap, int);
	buf->size = 1;
	if (token->width_field > 0)
		buf_pad(buf, padding_byte(token)
			, token->width_field, token->flags & MINUS_FLAG);
}

int		read_int(t_token *token, va_list ap, t_buf *buf)
{
	int					base;
	unsigned long long	value;

	base = 10;
	if (token->type == 'o')
		base = 8;
	else if (token->type == 'x' || token->type == 'X')
		base = 16;
	value = 0;
	if (token->type == 'o' || token->type == 'u'
		|| token->type == 'x' || token->type == 'X')
	{
		if (token->modifiers & LL_MODIFIER)
			value = va_arg(ap, unsigned long long);
		else if (token->modifiers & L_MODIFIER)
			value = va_arg(ap, unsigned long);
		else if (token->modifiers & HH_MODIFIER)
			value = (unsigned char)va_arg(ap, unsigned int);
		else if (token->modifiers & H_MODIFIER)
			value = (unsigned short)va_arg(ap, unsigned int);
		else
			value = va_arg(ap, unsigned int);
	}
	else
	{
		if (token->modifiers & LL_MODIFIER)
			value = va_arg(ap, long long);
		else if (token->modifiers & L_MODIFIER)
			value = va_arg(ap, long);
		else if (token->modifiers & HH_MODIFIER)
			value = (char)va_arg(ap, int);
		else if (token->modifiers & H_MODIFIER)
			value = (short)va_arg(ap, int);
		else
			value = va_arg(ap, int);
		if (value >> ((sizeof(long long) * 8) - 1))
		{
			value = ~value + 1;
			buf->str = ft_lltoa((long long)value);
			return (1);
		}
	}
	buf->str = ft_ulltoa_base(value, base);
	return (0);
}

void	convert_int(t_token *token, va_list ap, t_buf *buf)
{
	int	neg;
	int	can_expand;

	neg = read_int(token, ap, buf);
	if (!(buf->str))
		exit(1);
	buf->size = ft_strlen(buf->str);
	if (token->type == 'x')
		buf->str = ft_strtolower(buf->str);
	if (token->precision > 0 && buf->size < (size_t)token->precision)
	{
		buf_pad(buf, '0', token->precision, 0);
		if (!(buf->str))
			exit(1);
	}
	can_expand = token->flags & ZERO_FLAG
		&& token->precision < 0
		&& !(token->flags & MINUS_FLAG);
	if (token->width_field > 0 && can_expand)
	{
		buf_pad(buf, '0', token->width_field - (neg
				|| token->flags & PLUS_FLAG
				|| token->flags & SPACE_FLAG), 0);
		if (!(buf->str))
			exit(1);
	}
	if ((token->type == 'd' || token->type == 'i'))
	{
		if (neg)
			buf_prepend("-", buf);
		else if (token->flags & PLUS_FLAG)
			buf_prepend("+", buf);
		else if (token->flags & SPACE_FLAG)
			buf_prepend(" ", buf);
		if (buf->str == NULL)
			exit(1);
	}
	if ((buf->str)[0] != '0' && token->flags & HASH_FLAG)
	{
		if (token->type == 'o')
			buf_prepend("0", buf);
		else if (token->type == 'x')
			buf_prepend("0x", buf);
		else if (token->type == 'X')
			buf_prepend("0X", buf);
		if (!(buf->str))
			exit(1);
	}
	if (token->width_field > 0 && !can_expand)
		buf_pad(buf, ' ', token->width_field, token->flags & MINUS_FLAG);
}

void	convert_pointer(t_token *token, va_list ap, t_buf *buf)
{
	if (!(buf->str = ft_lltoa_base(va_arg(ap, t_intptr), 16)))
		exit(1);
	buf->size = ft_strlen(buf->str);
	buf->str = ft_strtolower(buf->str);
	buf_prepend("0x", buf);
	if (!(buf->str))
		exit(1);
	if (token->width_field > 0)
		buf_pad(buf, padding_byte(token)
			, token->width_field, token->flags & MINUS_FLAG);
}
