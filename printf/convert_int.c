/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 13:59:21 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/21 16:33:20 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

static unsigned long long	get_ullong(t_token *token, va_list ap)
{
	if (token->modifiers & Z_MODIFIER)
		return (va_arg(ap, size_t));
	else if (token->modifiers & LL_MODIFIER)
		return (va_arg(ap, unsigned long long));
	else if (token->modifiers & L_MODIFIER)
		return (va_arg(ap, unsigned long));
	else if (token->modifiers & HH_MODIFIER)
		return ((unsigned char)va_arg(ap, unsigned int));
	else if (token->modifiers & H_MODIFIER)
		return ((unsigned short)va_arg(ap, unsigned int));
	else
		return (va_arg(ap, unsigned int));
}

static long long			get_llong(t_token *token, va_list ap)
{
	if (token->modifiers & Z_MODIFIER)
		return (va_arg(ap, long));
	else if (token->modifiers & LL_MODIFIER)
		return (va_arg(ap, long long));
	else if (token->modifiers & L_MODIFIER)
		return (va_arg(ap, long));
	else if (token->modifiers & HH_MODIFIER)
		return ((char)va_arg(ap, int));
	else if (token->modifiers & H_MODIFIER)
		return ((short)va_arg(ap, int));
	else
		return (va_arg(ap, int));
}

static int					fill_buf(t_token *token, va_list ap, t_buf *buf)
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
		value = get_ullong(token, ap);
	else
	{
		value = get_llong(token, ap);
		if (value >> ((sizeof(long long) * 8) - 1))
		{
			value = ~value + 1;
			buf->str = ft_ulltoa(value);
			return (1);
		}
	}
	buf->str = (value == 0 && token->precision == 0)
		? ft_strnew(0) : ft_ulltoa_base(value, base);
	return (0);
}

void						convert_int(t_token *token, va_list ap, t_buf *buf)
{
	int	neg;
	int	is_zero;
	int	can_expand;
	int	offset;

	neg = fill_buf(token, ap, buf);
	if (!(buf->str))
		exit(1);
	buf->size = ft_strlen(buf->str);
	is_zero = (buf->str)[0] == '\0'
		|| ((buf->str)[0] == '0' && (buf->str)[1] == '\0');
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
		offset = 0;
		if ((token->type == 'd' || token->type == 'i')
			&& (buf->str)[0] != '\0'
			&& (neg || token->flags & PLUS_FLAG || token->flags & SPACE_FLAG))
			offset += 1;
		else if (token->flags & HASH_FLAG
			&& token->type == 'o'
			&& (!is_zero || token->precision == 0))
			offset += 1;
		else if (token->flags & HASH_FLAG
			&& (token->type == 'x' || token->type == 'X')
			&& !is_zero)
			offset += 2;
		buf_pad(buf, '0', token->width_field - offset, 0);
		if (!(buf->str))
			exit(1);
	}
	if ((token->type == 'd' || token->type == 'i') && (buf->str)[0] != '\0')
	{
		if (neg)
			buf_prepend("-", buf);
		else if (token->flags & PLUS_FLAG)
			buf_prepend("+", buf);
		else if (token->flags & SPACE_FLAG)
			buf_prepend(" ", buf);
		if (!(buf->str))
			exit(1);
	}
	if (token->flags & HASH_FLAG)
	{
		if (token->type == 'o'
			&& ((buf->str)[0] != '0' || token->precision == 0))
			buf_prepend("0", buf);
		else if ((token->type == 'x' || token->type == 'X') && !is_zero)
			buf_prepend("0X", buf);
		if (!(buf->str))
			exit(1);
	}
	if (token->type == 'x')
		buf->str = ft_strtolower(buf->str);
	if (token->width_field > 0 && !can_expand)
		buf_pad(buf, ' ', token->width_field, token->flags & MINUS_FLAG);
}
