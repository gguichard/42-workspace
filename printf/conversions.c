/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 22:57:10 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/14 23:03:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

char	*convert_str(t_pholder *holder, va_list args)
{
	char	*str;

	str = ft_strdup(va_arg(args, char *));
	if (holder->precision >= 0 && (int)ft_strlen(str) > holder->precision)
		str[holder->precision] = '\0';
	return (str);
}

char	*convert_char(t_pholder *holder, va_list args)
{
	char	*str;

	(void)holder;
	if (!(str = (char *)malloc(2 * sizeof(char *))))
		return (NULL);
	str[0] = (char)va_arg(args, int);
	str[1] = '\0';
	return (str);
}

char	*convert_decimal(t_pholder *holder, va_list args)
{
	(void)holder;
	return (ft_itoa(va_arg(args, int)));
}
