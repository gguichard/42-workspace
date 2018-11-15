/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 22:57:10 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/15 17:41:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

char	*convert_str(t_pholder *holder, va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	str = ft_strdup(str == NULL ? "(null)" : str);
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
		return (pad_string(str
			, padding_byte(holder)
			, holder->width_field
			, holder->flags & MINUS_FLAG));
	return (str);
}

char	*convert_decimal(t_pholder *holder, va_list args)
{
	int		nb;
	char	*str;

	nb = va_arg(args, int);
	str = ft_itoa_base(nb, base_from_type(holder));
	if (holder->type == 'x')
		str = ft_strtolower(str);
	if (holder->precision > 0)
		str = pad_string(str, '0', holder->precision, 0);
	if (nb > 0 && holder->flags & HASH_FLAG)
	{
		if (holder->type == 'x')
			str = ft_strjoin("0x", str);
		if (holder->type == 'X')
			str = ft_strjoin("0X", str);
		if (holder->type == 'o' && str[0] != '0')
			str = ft_strjoin("0", str);
	}
	if (holder->width_field > 0)
		str = pad_string(str
			, (holder->precision > 0 ? ' ' : padding_byte(holder))
			, holder->width_field
			, holder->flags & MINUS_FLAG);
	return (str);
}
