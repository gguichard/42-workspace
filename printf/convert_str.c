/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 13:58:54 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/19 14:01:05 by gguichar         ###   ########.fr       */
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
