/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 13:56:31 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/21 19:05:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

void	convert_other(t_token *tok, t_buf *buf)
{
	if (!(buf->str = (char *)malloc(1)))
		exit(1);
	(buf->str)[0] = tok->type;
	buf->size = 1;
	if (tok->width_field > 0 && buf->size < (size_t)tok->width_field)
		buf_pad(buf, pad_byte(tok), tok->width_field, tok->flags & MINUS_FLAG);
}

void	convert_pointer(t_token *tok, va_list ap, t_buf *buf)
{
	t_intptr	value;

	value = va_arg(ap, t_intptr);
	if (!value && tok->precision == 0)
		buf->str = ft_strnew(0);
	else
		buf->str = ft_lltoa_base(value, 16);
	if (!(buf->str))
		exit(1);
	buf->size = ft_strlen(buf->str);
	buf->str = ft_strtolower(buf->str);
	if (tok->precision > 0 && (size_t)tok->precision > buf->size)
		buf_pad(buf, '0', tok->precision, 0);
	if (tok->flags & ZERO_FLAG && !(tok->flags & MINUS_FLAG)
		&& tok->width_field > 2)
		buf_pad(buf, '0', tok->width_field - 2, 0);
	buf_prepend("0x", buf);
	if (!(buf->str))
		exit(1);
	if (tok->width_field > 0 && buf->size < (size_t)tok->width_field
		&& (!(tok->flags & ZERO_FLAG) || tok->flags & MINUS_FLAG))
		buf_pad(buf, pad_byte(tok)	, tok->width_field, tok->flags & MINUS_FLAG);
}
