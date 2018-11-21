/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 13:59:21 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/21 21:20:13 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

static unsigned long long	get_ullong(t_token *tok, va_list ap)
{
	if (tok->modifiers & Z_MODIFIER)
		return (va_arg(ap, size_t));
	else if (tok->modifiers & LL_MODIFIER)
		return (va_arg(ap, unsigned long long));
	else if (tok->modifiers & L_MODIFIER)
		return (va_arg(ap, unsigned long));
	else if (tok->modifiers & HH_MODIFIER)
		return ((unsigned char)va_arg(ap, unsigned int));
	else if (tok->modifiers & H_MODIFIER)
		return ((unsigned short)va_arg(ap, unsigned int));
	else
		return (va_arg(ap, unsigned int));
}

static long long			get_llong(t_token *tok, va_list ap)
{
	if (tok->modifiers & Z_MODIFIER)
		return (va_arg(ap, long));
	else if (tok->modifiers & LL_MODIFIER)
		return (va_arg(ap, long long));
	else if (tok->modifiers & L_MODIFIER)
		return (va_arg(ap, long));
	else if (tok->modifiers & HH_MODIFIER)
		return ((char)va_arg(ap, int));
	else if (tok->modifiers & H_MODIFIER)
		return ((short)va_arg(ap, int));
	else
		return (va_arg(ap, int));
}

static int					fill_buf(t_token *tok, va_list ap, t_buf *buf)
{
	int					base;
	unsigned long long	value;

	base = 10;
	if (tok->type == 'o')
		base = 8;
	else if (tok->type == 'x' || tok->type == 'X')
		base = 16;
	value = 0;
	if (tok->type == 'o' || tok->type == 'u'
		|| tok->type == 'x' || tok->type == 'X')
		value = get_ullong(tok, ap);
	else
	{
		value = get_llong(tok, ap);
		if (value >> ((sizeof(long long) * 8) - 1))
		{
			value = ~value + 1;
			buf->str = ft_ulltoa(value);
			return (1);
		}
	}
	if (value == 0 && tok->precision == 0)
		buf->str = ft_strnew(0);
	else
		buf->str = ft_ulltoa_base(value, base);
	return (0);
}

void						convert_int(t_token *tok, va_list ap, t_buf *buf)
{
	int	neg;
	int	is_zero;
	int	can_expand;
	int	offset;

	neg = fill_buf(tok, ap, buf);
	if (!(buf->str))
		exit(1);
	buf->size = ft_strlen(buf->str);
	is_zero = buf->size == 0 || (buf->size == 1 && (buf->str)[0] == '0');
	if (tok->precision > 0 && buf->size < (size_t)tok->precision)
	{
		buf_pad(buf, '0', tok->precision, 0);
		if (!(buf->str))
			exit(1);
	}
	can_expand = tok->precision < 0
		&& tok->flags & ZERO_FLAG && !(tok->flags & MINUS_FLAG);
	if (tok->width_field > 0 && can_expand)
	{
		offset = 0;
		if ((tok->type == 'd' || tok->type == 'i')
			&& (neg || tok->flags & PLUS_FLAG || tok->flags & SPACE_FLAG))
			offset += 1;
		else if (tok->flags & HASH_FLAG
			&& tok->type == 'o'
			&& (!is_zero || tok->precision == 0))
			offset += 1;
		else if (tok->flags & HASH_FLAG
			&& (tok->type == 'x' || tok->type == 'X')
			&& !is_zero)
			offset += 2;
		buf_pad(buf, '0', tok->width_field - offset, 0);
		if (!(buf->str))
			exit(1);
	}
	if ((tok->type == 'd' || tok->type == 'i'))
	{
		if (neg)
			buf_prepend("-", buf);
		else if (tok->flags & PLUS_FLAG)
			buf_prepend("+", buf);
		else if (tok->flags & SPACE_FLAG)
			buf_prepend(" ", buf);
		if (!(buf->str))
			exit(1);
	}
	if (tok->flags & HASH_FLAG)
	{
		if (tok->type == 'o'
			&& ((buf->str)[0] != '0' || tok->precision == 0))
			buf_prepend("0", buf);
		else if ((tok->type == 'x' || tok->type == 'X') && !is_zero)
			buf_prepend("0X", buf);
		if (!(buf->str))
			exit(1);
	}
	if (tok->type == 'x')
		buf->str = ft_strtolower(buf->str);
	if (tok->width_field > 0
		&& buf->size < (size_t)tok->width_field && !can_expand)
		buf_pad(buf, ' ', tok->width_field, tok->flags & MINUS_FLAG);
}
