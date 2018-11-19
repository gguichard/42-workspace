/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:29:01 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/19 17:38:41 by gguichar         ###   ########.fr       */
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
	else if (token->type == 'f')
		convert_double(token, ap, &buf);
	else if (token->type == '%')
		convert_percent(token, ap, &buf);
	else if (token->type != '\0')
		return (write(1, &token->type, 1));
	else
		return (0);
	buf.size = write(1, buf.str, buf.size);
	free(buf.str);
	return (buf.size);
}

int	write_and_parse(const char *format, va_list ap)
{
	char	*flag;
	t_token	token;
	int		total_write;

	total_write = 0;
	while ((flag = ft_strchr(format, '%')) != NULL)
	{
		if (flag > format)
			total_write += write(1, format, (size_t)(flag - format));
		token.flags = 0;
		token.modifiers = 0;
		token.precision = -1;
		token.width_field = -1;
		token.type = 0;
		format = parse_token(flag + 1, &token);
		if (token.type == 0)
			return (total_write);
		total_write += print_token(&token, ap);
		format++;
	}
	if (*format != '\0')
		total_write += write(1, format, ft_strlen(format));
	return (total_write);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		ret;

	va_start(args, format);
	ret = write_and_parse(format, args);
	va_end(args);
	return (ret);
}
