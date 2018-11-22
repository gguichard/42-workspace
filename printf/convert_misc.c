/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 13:56:31 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/22 12:50:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "printf.h"
#include "libft.h"

void	convert_other(t_token *tok)
{
	if (!(tok->buf.str = (char *)malloc(1)))
		exit(1);
	(tok->buf.str)[0] = tok->type;
	tok->buf.size = 1;
	if (tok->width_field > 0 && tok->buf.size < tok->width_field)
		buf_pad(&(tok->buf), pad_byte(tok), tok->width_field
			, tok->flags & MINUS_FLAG);
}

void	convert_pointer(t_token *tok, va_list ap)
{
	intptr_t	value;

	value = va_arg(ap, intptr_t);
	if (!value && tok->precision == 0)
		tok->buf.str = ft_strnew(0);
	else
		tok->buf.str = ft_lltoa_base(value, 16);
	if (!(tok->buf.str))
		exit(1);
	tok->buf.size = ft_strlen(tok->buf.str);
	tok->buf.str = ft_strtolower(tok->buf.str);
	if (tok->precision > 0 && tok->precision > tok->buf.size)
		buf_pad(&(tok->buf), '0', tok->precision, 0);
	if (tok->flags & ZERO_FLAG && !(tok->flags & MINUS_FLAG)
		&& tok->width_field > 2)
		buf_pad(&(tok->buf), '0', tok->width_field - 2, 0);
	buf_prepend("0x", &(tok->buf));
	if (!(tok->buf.str))
		exit(1);
	if (tok->width_field > 0 && tok->buf.size < tok->width_field
		&& (!(tok->flags & ZERO_FLAG) || tok->flags & MINUS_FLAG))
		buf_pad(&(tok->buf), pad_byte(tok), tok->width_field
			, tok->flags & MINUS_FLAG);
}
