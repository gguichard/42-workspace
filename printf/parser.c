/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 09:05:16 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/17 10:19:52 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "printf.h"
#include "libft.h"

static int	parse_flags(t_pholder *holder, const char *str)
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
		return (0);
	return (1);
}

static int	parse_fieldwidth_precision(t_pholder *holder, const char *str)
{
	int	offset;

	offset = 0;
	while (ft_isdigit(str[offset]))
	{
		if (holder->width_field < 0)
			holder->width_field = 0;
		holder->width_field *= 10;
		holder->width_field += (str[offset] - '0');
		offset++;
	}
	if (str[offset] == '.')
	{
		holder->precision = 0;
		offset++;
		while (ft_isdigit(str[offset]))
		{
			holder->precision *= 10;
			holder->precision += (str[offset] - '0');
			offset++;
		}
	}
	return (offset);
}

static int	parse_modifiers(t_pholder *holder, const char *str)
{
	if (*str == 'h')
	{
		if (holder->modifiers & H_MODIFIER)
			holder->modifiers |= HH_MODIFIER;
		holder->modifiers |= H_MODIFIER;
	}
	else if (*str == 'l')
	{
		if (holder->modifiers & L_MODIFIER)
			holder->modifiers |= LL_MODIFIER;
		holder->modifiers |= L_MODIFIER;
	}
	else
		return (0);
	return (1);
}

static int	parse_placeholder(const char *format, t_pholder *holder)
{
	int	old_offset;
	int	offset;

	holder->flags = 0;
	holder->width_field = -1;
	holder->precision = -1;
	holder->modifiers = 0;
	offset = 0;
	while (format[offset] != '\0')
	{
		old_offset = offset;
		offset += parse_flags(holder, &(format[offset]));
		offset += parse_fieldwidth_precision(holder, &(format[offset]));
		offset += parse_modifiers(holder, &(format[offset]));
		if (offset == old_offset)
		{
			holder->type = format[offset];
			break ;
		}
	}
	return (offset + 1);
}

int			parse(const char *str, va_list args)
{
	size_t		len;
	const char	*parse;
	t_pholder	holder;
	int			ret;

	len = ft_strlen(str);
	ret = 0;
	while ((parse = ft_memchr(str, '%', len)) != NULL)
	{
		if (parse > str)
			ret += write(1, str, (size_t)(parse - str));
		str = parse + 1;
		str += parse_placeholder(str, &holder);
		ret += print_placeholder(&holder, args);
	}
	if (parse == NULL)
		ret += write(1, str, ft_strlen(str));
	return (ret);
}
