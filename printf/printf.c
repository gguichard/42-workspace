/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:29:01 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/14 16:57:57 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "printf.h"
#include "libft.h"

void		print_placeholder(t_pholder *holder, va_list args)
{
	char	*str;

	if (holder->type == 's')
		str = ft_strdup(va_arg(args, char *));
	else if (holder->type == 'c')
	{
		if (!(str = (char *)malloc(2 * sizeof(char *))))
			exit(1);
		str[0] = va_arg(args, char);
		str[1] = '\0';
	}
	else if (holder->type == 'd' || holder->type == 'i')
	{
		str = ft_itoa(va_arg(args, int));
	}
	else
	{
		write(1, &(holder->type), 1);
		return ;
	}
	if (holder->width_field > 0 && !(str = pad_string(str
			, (holder->flags & ZERO_FLAG) ? '0' : ' ', holder->width_field)))
		exit(1);
	write(1, str, ft_strlen(str));
	free(str);
}

int			ft_printf(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	parse(format, args);
	va_end(args);
	return (1);
}
