/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:29:01 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/18 16:39:33 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "printf.h"
#include "libft.h"

int	print_token(t_token *token, va_list ap)
{
	char	*str;

	if (token->type == 's')
		str = convert_str(token, ap);
	else if (token->type == 'c')
		str = convert_char(token, ap);
	else if (token->type == 'p')
		str = convert_pointer(token, ap);
	else if (token->type == 'd' || token->type == 'i' || token->type == 'u'
		|| token->type == 'o' || token->type == 'x' || token->type == 'X')
		str = convert_int(token, ap);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			ret;

	va_start(args, format);
	ret = write_and_parse(format, args);
	va_end(args);
	return (ret);
}
