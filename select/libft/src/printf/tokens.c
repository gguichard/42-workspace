/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 08:22:53 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/22 12:02:26 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

static void	set_wildcards(t_token *tok, va_list ap)
{
	int	tmp;

	if (tok->wildcards & WIDTH_WILDCARD)
	{
		tmp = va_arg(ap, int);
		if (tmp < 0 && tok->width_field < 0)
		{
			tmp = -tmp;
			tok->flags |= MINUS_FLAG;
		}
		tok->width_field = (tok->width_field < 0) ? tmp : tok->width_field;
	}
	if (tok->wildcards & PRECISION_WILDCARD)
	{
		tmp = va_arg(ap, int);
		tok->precision = (tok->precision < 0) ? tmp : tok->precision;
	}
}

void		pf_convert(t_token *tok, va_list ap)
{
	set_wildcards(tok, ap);
	if (tok->type == 'S' || tok->type == 'C'
		|| tok->type == 'D' || tok->type == 'O' || tok->type == 'U')
	{
		tok->type = ft_tolower(tok->type);
		tok->modifiers = L_MODIFIER;
	}
	if (tok->type == 's')
		convert_str(tok, ap);
	else if (tok->type == 'c')
		convert_char(tok, ap);
	else if (tok->type == 'd' || tok->type == 'i'
		|| tok->type == 'o' || tok->type == 'u'
		|| tok->type == 'x' || tok->type == 'X')
		convert_int(tok, ap);
	else if (tok->type == 'f' || tok->type == 'F')
		convert_double(tok, ap);
	else if (tok->type == 'p')
		convert_pointer(tok, ap);
	else if (tok->type != 0)
		convert_other(tok);
}
