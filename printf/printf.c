/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:29:01 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/16 15:36:43 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "printf.h"
#include "libft.h"

void		print_placeholder(t_pholder *holder, va_list args)
{
	char	*str;

	if (holder->type == 's')
		str = convert_str(holder, args);
	else if (holder->type == 'c')
		str = convert_char(holder, args);
	else if (holder->type == 'd' || holder->type == 'i' || holder->type == 'o'
		|| holder->type == 'u' || holder->type == 'x' || holder->type == 'X')
		str = convert_decimal(holder, args);
	else if (holder->type == 'f')
		str = convert_double(holder, args);
	else if (holder->type == 'p')
		str = convert_pointer(holder, args);
	else
	{
		write(1, &(holder->type), 1);
		return ;
	}
	if (str == NULL)
		exit(1);
	write(1, str, ft_strlen(str));
	free(str);
}

int			ft_printf(const char *format, ...)
{
	va_list		args;

	va_start(args, format);
	parse(format, args);
	va_end(args);
	return (1);
}
