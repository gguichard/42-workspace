/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:10:19 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/21 23:24:30 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

void	convert_double(t_token *tok, va_list ap, t_buf *buf)
{
	long double	value;
	char		*tmp;
	double		pow;
	int			i;

	if (tok->modifiers & LUP_MODIFIER)
		value = va_arg(ap, long double);
	else
		value = va_arg(ap, double);
	if (!(buf->str = ft_lltoa((long long)value)))
		exit(1);
	if (tok->precision < 0)
		tok->precision = 6;
	buf->size = ft_strlen(buf->str);
	if (tok->precision != 0)
	{
		tmp = buf->str;
		if (!(buf->str = (char *)malloc(buf->size + tok->precision + 1)))
			exit(1);
		ft_memcpy(buf->str, tmp, buf->size);
		free(tmp);
		(buf->str)[buf->size] = '.';
		buf->size += tok->precision + 1;
	}
	value -= (long long)value;
	if (value < 0)
		value = -value;
	pow = 1.0;
	i = 0;
	while (i < tok->precision)
	{
		pow *= 10.0;
		(buf->str)[buf->size - tok->precision + i]
			= (((unsigned long long)(value * pow) % 10) + '0');
		i++;
	}
}
