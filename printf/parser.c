/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 09:05:16 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/14 16:10:42 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "printf.h"
#include "libft.h"

static int	parse_flags(const char *format, t_pholder *holder)
{
	int		offset;
	char	c;

	offset = 0;
	while ((c = format[offset]) != '\0')
	{
		if (c == '#')
			holder->flags |= HASH_FLAG;
		else if (c == '0')
			holder->flags |= ZERO_FLAG;
		else if (c == '-')
			holder->flags |= MINUS_FLAG;
		else if (c == ' ')
			holder->flags |= SPACE_FLAG;
		else if (c == '+')
			holder->flags |= PLUS_FLAG;
		else
			break ;
		offset++;
	}
	return (offset);
}

static int	parse_fieldwidth_precision(const char *format, t_pholder *holder)
{
	int	offset;

	offset = 0;
	while (ft_isdigit(format[offset]))
	{
		holder->width_field *= 10;
		holder->width_field += (format[offset] - '0');
		offset++;
	}
	if (format[offset] == '.')
	{
		offset++;
		while (ft_isdigit(format[offset]))
		{
			holder->precision *= 10;
			holder->precision += (format[offset] - '0');
			offset++;
		}
	}
	return (offset);
}

static int	parse_modifiers(const char *format, t_pholder *holder)
{
	int		offset;
	char	c;

	offset = 0;
	while ((c = format[offset]) != '\0')
	{
		if (c == 'h')
		{
			holder->modifiers |= H_MODIFIER;
			if (holder->modifiers & H_MODIFIER)
				holder->modifiers |= HH_MODIFIER;
		}
		else if (format[offset] == 'l')
		{
			holder->modifiers |= L_MODIFIER;
			if (holder->modifiers & L_MODIFIER)
				holder->modifiers |= LL_MODIFIER;
		}
		else
			break ;
	}
	return (offset);
}

static int	parse_placeholder(const char *format, t_pholder *holder)
{
	int	offset;

	holder->flags = 0;
	holder->width_field = 0;
	holder->precision = 0;
	holder->modifiers = 0;
	offset = 0;
	offset += parse_flags(format, holder);
	offset += parse_fieldwidth_precision(&(format[offset]), holder);
	offset += parse_modifiers(&(format[offset]), holder);
	holder->type = format[offset];
	return (offset + 1);
}

void		parse(const char *str, va_list args)
{
	size_t		len;
	const char	*parse;
	t_pholder	holder;

	len = ft_strlen(str);
	while ((parse = ft_memchr(str, '%', len)) != NULL)
	{
		if (parse > str)
			write(1, str, (size_t)(parse - str));
		str = parse + 1;
		str += parse_placeholder(str, &holder);
		print_placeholder(&holder, args);
	}
	if (parse == NULL)
		write(1, str, ft_strlen(str));
}
