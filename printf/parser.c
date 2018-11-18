/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 09:05:16 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/18 00:57:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "printf.h"
#include "libft.h"

static char	*parse_flags(char *str, t_pholder *holder)
{
	if (*str == '#')
		holder->flags |= HASH_FLAG;
	else if (*str == '0')
		holder->flags |= ZERO_FLAG;
	else if (*str == '-')
		holder->flags |= MINUS_FLAG;
	else if (*str == ' ')
		holder->flags |= SPACE_FLAG;
	else if (*str == '+')
		holder->flags |= PLUS_FLAG;
	else
		return (str);
	return (str + 1);
}

static char	*parse_fieldwidth_precision(char *str, t_pholder *holder)
{
	while (ft_isdigit(*str))
	{
		if (holder->width_field < 0)
			holder->width_field = 0;
		holder->width_field *= 10;
		holder->width_field += (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		holder->precision = 0;
		str++;
		while (ft_isdigit(*str))
		{
			holder->precision *= 10;
			holder->precision += (*str - '0');
			str++;
		}
	}
	return (str);
}

static char	*parse_modifiers(char *str, t_pholder *holder)
{
	if (*str == 'h')
	{
		str++;
		if (*str != 'h')
			holder->modifiers |= H_MODIFIER;
		else
		{
			holder->modifiers |= HH_MODIFIER;
			str++;
		}
	}
	else if (*str == 'l')
	{
		str++;
		if (*str != 'l')
			holder->modifiers |= L_MODIFIER;
		else
		{
			holder->modifiers |= LL_MODIFIER;
			str++;
		}
	}
	return (str);
}

static char	*parse_placeholder(char *format, t_pholder *holder)
{
	char	*before;

	holder->flags = 0;
	holder->width_field = -1;
	holder->precision = -1;
	holder->modifiers = 0;
	holder->type = '\0';
	while (*format != '\0' && holder->type == '\0')
	{
		before = format;
		format = parse_flags(format, holder);
		format = parse_fieldwidth_precision(format, holder);
		format = parse_modifiers(format, holder);
		if (before == format)
			holder->type = *format;
	}
	return (format + (format != '\0'));
}

int			parse(const char *str, va_list args)
{
	char		*start;
	t_pholder	holder;
	int			ret;

	ret = 0;
	while ((start = ft_strchr(str, '%')) != NULL)
	{
		if (start > str)
			ret += write(1, str, (size_t)(start - str));
		str = parse_placeholder(start + 1, &holder);
		if (holder.type != '\0')
			ret += print_placeholder(&holder, args);
	}
	if (*str != '\0')
		ret += write(1, str, ft_strlen(str));
	return (ret);
}
