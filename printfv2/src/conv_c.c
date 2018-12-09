/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 10:26:35 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/09 19:58:26 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	pf_conv_c(t_pf *pf)
{
	char	c;

	c = (char)va_arg(pf->ap, int);
	pf->w_field -= 1;
	if (pf->w_field > 0 && !(pf->flags & MINUS_FLAG))
		buf_pad(pf);
	buf_char(pf, c, 1);
	if (pf->w_field > 0 && pf->flags & MINUS_FLAG)
		buf_pad(pf);
}
