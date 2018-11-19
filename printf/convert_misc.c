/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 13:56:31 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/19 15:08:30 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

void	convert_percent(t_token *token, va_list ap, t_buf *buf)
{
	(void)ap;
	if (!(buf->str = (char *)malloc(1)))
		exit(1);
	(buf->str)[0] = '%';
	buf->size = 1;
	if (token->width_field > 0)
		buf_pad(buf, padding_byte(token)
			, token->width_field, token->flags & MINUS_FLAG);
}

void	convert_pointer(t_token *token, va_list ap, t_buf *buf)
{
	t_intptr	value;

	value = va_arg(ap, t_intptr);
	if (!value && token->precision == 0)
		buf->str = ft_strnew(0);
	else
		buf->str = ft_lltoa_base(value, 16);
	if (!(buf->str))
		exit(1);
	buf->size = ft_strlen(buf->str);
	buf->str = ft_strtolower(buf->str);
	if (token->precision > 0 && (size_t)token->precision > buf->size)
		buf_pad(buf, '0', token->precision, 0);
	buf_prepend("0x", buf);
	if (!(buf->str))
		exit(1);
	if (token->width_field > 0)
		buf_pad(buf, padding_byte(token)
			, token->width_field, token->flags & MINUS_FLAG);
}
