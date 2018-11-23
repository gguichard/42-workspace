/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 12:59:53 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/22 13:16:17 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "printf.h"

static unsigned long long	get_ullong(t_token *tok, va_list ap)
{
	if (tok->modifiers & J_MODIFIER)
		return (va_arg(ap, uintmax_t));
	else if (tok->modifiers & LL_MODIFIER)
		return (va_arg(ap, unsigned long long));
	else if (tok->modifiers & L_MODIFIER)
		return (va_arg(ap, unsigned long));
	else if (tok->modifiers & Z_MODIFIER)
		return (va_arg(ap, size_t));
	else if (tok->modifiers & HH_MODIFIER)
		return ((unsigned char)va_arg(ap, unsigned int));
	else if (tok->modifiers & H_MODIFIER)
		return ((unsigned short)va_arg(ap, unsigned int));
	else
		return (va_arg(ap, unsigned int));
}

static long long			get_llong(t_token *tok, va_list ap)
{
	if (tok->modifiers & J_MODIFIER)
		return (va_arg(ap, intmax_t));
	else if (tok->modifiers & LL_MODIFIER)
		return (va_arg(ap, long long));
	else if (tok->modifiers & L_MODIFIER)
		return (va_arg(ap, long));
	else if (tok->modifiers & Z_MODIFIER)
		return (va_arg(ap, long));
	else if (tok->modifiers & HH_MODIFIER)
		return ((char)va_arg(ap, int));
	else if (tok->modifiers & H_MODIFIER)
		return ((short)va_arg(ap, int));
	else
		return (va_arg(ap, int));
}

int							intval_to_buf(t_token *tok, va_list ap)
{
	int					base;
	unsigned long long	value;

	base = 10;
	if (tok->type == 'o')
		base = 8;
	else if (ft_tolower(tok->type) == 'x')
		base = 16;
	value = 0;
	if (tok->type == 'o' || tok->type == 'u' || ft_tolower(tok->type) == 'x')
		value = get_ullong(tok, ap);
	else
	{
		value = get_llong(tok, ap);
		if (value >> ((sizeof(long long) * 8) - 1))
		{
			tok->buf.str = ft_ulltoa(~value + 1);
			return (1);
		}
	}
	if (value == 0 && tok->precision == 0)
		tok->buf.str = ft_strnew(0);
	else
		tok->buf.str = ft_ulltoa_base(value, base);
	return (0);
}
