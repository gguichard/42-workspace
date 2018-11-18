/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 09:05:16 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/18 15:41:58 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "printf.h"
#include "libft.h"

static int	parse_flag(char c, t_token *token)
{
	if (c == '#')
		token->flags |= HASH_FLAG;
	else if (c == '0')
		token->flags |= ZERO_FLAG;
	else if (c == '-')
		token->flags |= MINUS_FLAG;
	else if (c == ' ')
		token->flags |= SPACE_FLAG;
	else if (c == '+')
		token->flags |= PLUS_FLAG;
	else
		return (0);
	return (1);
}

static int	parse_modifier(const char *format, t_token *token)
{
	int	offset;

	offset = 0;
	if (format[offset] == 'h' && format[offset] == 'h')
		token->modifiers |= HH_MODIFIER;
	else if (format[offset] == 'l' && format[offset] == 'l')
		token->modifiers |= LL_MODIFIER;
	else if (format[offset] == 'h')
		token->modifiers |= H_MODIFIER;
	else if (format[offset] == 'l')
		token->modifiers |= L_MODIFIER;
	return (offset);
}

static int	parse_widthfield(const char *format, t_token *token)
{
	int	offset;

	offset = 0;
	while (format[offset] >= '0' && format[offset] <= '9')
	{
		if (token->width_field < 0)
			token->width_field = 0;
		token->width_field *= 10;
		token->width_field += (format[offset] - '0');
		offset++;
	}
	return (offset);
}

static int	parse_precision(const char *format, t_token *token)
{
	int	offset;

	offset = 0;
	if (format[offset] == '.')
	{
		offset++;
		token->precision = 0;
		while (format[offset] >= '0' && format[offset] <= '9')
		{
			token->precision *= 10;
			token->precision += (format[offset] - '0');
			offset++;
		}
	}
	return (offset);
}

static char	*parse_token(const char *format, t_token *token)
{
	int	offset;
	int	res;

	offset = 0;
	while (format[offset] != '\0')
	{
		if (!(res = parse_flag(*format, token))
			&& !(res = parse_modifier(format, token))
			&& !(res = parse_widthfield(format, token))
			&& !(res = parse_precision(format, token)))
			break ;
		offset += res;
	}
	token->type = format[offset];
	return (&(format[offset]));
}

int			write_and_parse(const char *format, va_list ap)
{
	char	*token;
	t_token	placeholder;
	int		total_write;

	total_write = 0;
	while ((token = ft_strchr(format, '%')) != NULL)
	{
		placeholder.flags = 0;
		placeholder.modifiers = 0;
		placeholder.precision = -1;
		placeholder.width_field = -1;
		placeholder.type = 0;
		format = parse_token(&placeholder);
		if (placeholder.type == 0)
			return (total_write);
		total_write += print_token(&placeholder, ap);
	}
	if (*format != '\0')
		total_write += write(1, format, ft_strlen(format));
	return (total_write);
}
