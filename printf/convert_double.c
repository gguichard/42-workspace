/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:10:19 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/19 17:53:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

void	convert_double(t_token *token, va_list ap, t_buf *buf)
{
	double		value;
	int			sign;
	int			exponent;
	long long	fraction;
	long long	bits;

	(void)token;
	value = va_arg(ap, double);
	bits = *((long long *)&value);
	sign = bits >> 63;
	exponent = ((bits << 1) >> 53) - 1023;
	fraction = bits << 12;
	fraction <<= exponent;
	while (!(fraction & 1))
		fraction >>= 1;
	buf->str = ft_lltoa(fraction);
	buf->size = ft_strlen(buf->str);
}
