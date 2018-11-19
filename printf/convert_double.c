/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:10:19 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/20 00:15:58 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

void	convert_double(t_token *token, va_list ap, t_buf *buf)
{
	long double	value;
	long long	pow;
	int			i;

	if (token->modifiers & LUP_MODIFIER)
		value = va_arg(ap, long double);
	else
		value = va_arg(ap, double);
	buf->str = ft_lltoa((long long)value);
	if (!(buf->str))
		exit(1);
	value = value < 0 ? -value : value;
	if (token->precision < 0)
		token->precision = 6;
	buf->size = ft_strlen(buf->str);
	if (token->precision != 0)
	{
		if (!(buf->str = ft_strjoin_free(buf->str, ".")))
			exit(1);
		(buf->size)++;
	}
	pow = 1;
	i = 0;
	while (i < token->precision)
	{
		pow *= 10;
		if (!(buf->str = ft_strjoin_free(buf->str
			, ft_lltoa((long long)((value - (long long)value) * pow) % 10))))
			exit(1);
		(buf->size)++;
		i++;
	}
}
