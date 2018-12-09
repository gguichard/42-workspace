/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 23:37:25 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/09 10:35:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

void	pf_conv_s(t_pf *pf)
{
	char	*str;

	if (!(str = va_arg(pf->ap, char *)))
		str = "(null)";
	if (pf->precision < 0)
		pf->precision = ft_strlen(str);
	else
		pf->precision = ft_min(pf->precision, ft_strlen(str));
	if (pf->w_field > 0)
		pf->w_field -= pf->precision;
	if (pf->w_field > 0 && !(pf->flags & MINUS_FLAG))
		buf_pad(pf);
	buf_write(pf, str, pf->precision);
	if (pf->w_field > 0 && pf->flags & MINUS_FLAG)
		buf_pad(pf);
}
