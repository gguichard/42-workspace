/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:10:19 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/02 14:56:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

static long double	ft_tenpow(int pow)
{
	long double	res;

	res = 1.0;
	while (pow--)
		res *= 10.0;
	return (res);
}

static int			double_precision(t_token *tok)
{
	char	*tmp;

	if (tok->precision < 0)
		tok->precision = 6;
	if (tok->precision != 0)
	{
		if (!(tmp = (char *)malloc(tok->buf.size + tok->precision + 1)))
			return (0);
		ft_memcpy(tmp, tok->buf.str, tok->buf.size);
		free(tok->buf.str);
		tmp[tok->buf.size] = '.';
		tok->buf.str = tmp;
		tok->buf.size += tok->precision + 1;
	}
	return (1);
}

void				convert_double(t_token *tok, va_list ap)
{
	long double	value;
	int			i;

	if (tok->modifiers & LUP_MODIFIER)
		value = va_arg(ap, long double);
	else
		value = va_arg(ap, double);
	if (!(tok->buf.str = ft_lltoa((long long)value)))
		exit(1);
	tok->buf.size = ft_strlen(tok->buf.str);
	if (!double_precision(tok))
		exit(1);
	value -= (long long)value;
	if (value < 0)
		value = -value;
	value *= ft_tenpow(tok->precision + 1);
	if ((unsigned long long)value % 10 >= 5)
		value += 1;
	i = tok->buf.size;
	while (i > (tok->buf.size - tok->precision))
	{
		value /= 10.0;
		(tok->buf.str)[i - 1] = (((unsigned long long)value % 10) + '0');
		i--;
	}
}
