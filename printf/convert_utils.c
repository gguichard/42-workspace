/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 20:18:25 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/16 20:25:30 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

static char	*signed_decimal(t_pholder *holder, va_list args)
{
	if (holder->modifiers & HH_MODIFIER)
		return (ft_lltoa((char)va_arg(args, int)));
	else if (holder->modifiers & H_MODIFIER)
		return (ft_lltoa((short)va_arg(args, int)));
	else if (holder->modifiers & LL_MODIFIER)
		return (ft_lltoa(va_arg(args, long long)));
	else if (holder->modifiers & L_MODIFIER)
		return (ft_lltoa(va_arg(args, long)));
	return (ft_lltoa(va_arg(args, int)));
}

static char	*unsigned_decimal(t_pholder *holder, va_list args)
{
	int	base;

	base = 10;
	if (holder->type == 'o')
		base = 8;
	else if (holder->type == 'x' || holder->type == 'X')
		base = 16;
	if (holder->modifiers & HH_MODIFIER)
		return (ft_ulltoa_base((unsigned char)va_arg(args, unsigned int)
			, base));
	else if (holder->modifiers & H_MODIFIER)
		return (ft_ulltoa_base((unsigned short)va_arg(args, unsigned int)
			, base));
	else if (holder->modifiers & LL_MODIFIER)
		return (ft_ulltoa_base(va_arg(args, unsigned long long), base));
	else if (holder->modifiers & L_MODIFIER)
		return (ft_ulltoa_base(va_arg(args, unsigned long), base));
	return (ft_ulltoa_base(va_arg(args, unsigned int), base));
}

char		*decimal_from_type(t_pholder *holder, va_list args)
{
	if (holder->type == 'd' || holder->type == 'i')
		return (signed_decimal(holder, args));
	return (unsigned_decimal(holder, args));
}
