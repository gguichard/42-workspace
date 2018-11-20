/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:10:19 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/20 08:08:58 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

void	convert_double(t_token *token, va_list ap, t_buf *buf)
{
	long double			value;
	double				pow;
	int					i;

	if (token->modifiers & LUP_MODIFIER)
		value = va_arg(ap, long double);
	else
		value = va_arg(ap, double);
	if (!(buf->str = ft_lltoa((long long)value)))
		exit(1);
	if (token->precision < 0)
		token->precision = 6;
	buf->size = ft_strlen(buf->str);
	if (token->precision != 0)
	{
		if (!(buf->str = ft_strjoin_free(buf->str, ".")))
			exit(1);
		(buf->size)++;
	}
	value -= (long long)value;
	if (value < 0)
		value = -value;
	pow = 1.0;
	i = 0;
	while (i < token->precision - 1)
	{
		pow *= 10.0;
		if (!(buf->str = ft_strjoin_free(buf->str
			, ft_itoa((unsigned long long)(value * pow) % 10))))
			exit(1);
		(buf->size)++;
		i++;
	}
	if (i < token->precision)
	{
		if (!(buf->str = ft_strjoin_free(buf->str
			, ft_itoa(((unsigned long long)(value * pow) % 10)
				+ (((unsigned long long)(value * pow * 10.0) % 10) >= 5)))))
			exit(1);
		(buf->size++);
		i++;
	}
}
