/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 22:57:10 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/17 00:03:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

char	*convert_str(t_pholder *holder, va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	if (!(str = ft_strdup(str == NULL ? "(null)" : str)))
		return (NULL);
	if (holder->precision >= 0 && ft_strlen(str) > (size_t)holder->precision)
		str[holder->precision] = '\0';
	return (str);
}

char	*convert_char(t_pholder *holder, va_list args)
{
	char	*str;

	if (!(str = (char *)malloc(2 * sizeof(char *))))
		return (NULL);
	str[0] = (char)va_arg(args, int);
	str[1] = '\0';
	if (holder->width_field > 0)
	{
		return (pad_string(str
			, padding_byte(holder)
			, holder->width_field
			, holder->flags & MINUS_FLAG));
	}
	return (str);
}

char	*convert_decimal(t_pholder *holder, va_list args)
{
	char	*str;

	if (!(str = decimal_from_type(holder, args)))
		return (NULL);
	if (holder->type == 'x')
		str = ft_strtolower(str);
	if (holder->precision > 0)
		str = pad_string(str, '0', holder->precision, 0);
	if ((holder->type == 'd' || holder->type == 'i') && str[0] != '-')
	{
		if (holder->flags & PLUS_FLAG)
			str = str_prepend("+", str);
		else if (holder->flags & SPACE_FLAG)
			str = str_prepend(" ", str);
		if (str == NULL)
			return (NULL);
	}
	if (str[0] != '0' && holder->flags & HASH_FLAG)
	{
		if (holder->type == 'o')
			str = str_prepend("0", str);
		else if (holder->type == 'x')
			str = str_prepend("0x", str);
		else if (holder->type == 'X')
			str = str_prepend("0X", str);
		if (str == NULL)
			return (NULL);
	}
	if (holder->width_field > 0)
		str = pad_string(str
			, (holder->precision > 0 ? ' ' : padding_byte(holder))
			, holder->width_field, holder->flags & MINUS_FLAG);
	return (str);
}

char	*convert_double(t_pholder *holder, va_list args)
{
	char		*str;
	double		value;
	long long	bits;
	int			sign;
	int			exponent;
	long long	fraction;

	value = va_arg(args, double);
	if (holder->precision < 0)
		holder->precision = 6;
	if (holder->precision > 0)
	{
		bits = *((long long *)&value);
		sign = bits >> 63;
		exponent = (bits << 1) >> 53;
		fraction = (bits << 12) >> 12;
	}
	return (str = NULL);
}

char	*convert_pointer(t_pholder *holder, va_list args)
{
	char	*str;

	if (!(str = ft_lltoa_base(va_arg(args, t_intptr), 16)))
		return (NULL);
	str = ft_strtolower(str);
	if (!(str = str_prepend("0x", str)))
		return (NULL);
	if (holder->width_field > 0)
		str = pad_string(str
			, padding_byte(holder)
			, holder->width_field
			, holder->flags & MINUS_FLAG);
	return (str);
}
