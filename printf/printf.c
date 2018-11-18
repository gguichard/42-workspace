/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:29:01 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/18 22:37:15 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "printf.h"
#include "libft.h"

int	print_token(t_token *token, va_list ap)
{
	t_buf	buf;

	buf.str = NULL;
	buf.size = 0;
	if (token->type == 's')
		convert_str(token, ap, &buf);
	else if (token->type == 'c')
		convert_char(token, ap, &buf);
	else if (token->type == 'p')
		convert_pointer(token, ap, &buf);
	else if (token->type == 'd' || token->type == 'i' || token->type == 'u'
		|| token->type == 'o' || token->type == 'x' || token->type == 'X')
		convert_int(token, ap, &buf);
	else if (token->type != '\0')
		return (write(1, &token->type, 1));
	else
		return (0);
	return (write(1, buf.str, buf.size));
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
