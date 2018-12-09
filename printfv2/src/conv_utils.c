/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 19:14:14 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/09 19:36:42 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"

long long			pf_value(t_pf *pf)
{
	if (pf->flags & HH_MODIFIER)
		return (char)(va_arg(pf->ap, int));
	else if (pf->flags & H_MODIFIER)
		return (short)(va_arg(pf->ap, int));
	else if (pf->flags & L_MODIFIER)
		return (va_arg(pf->ap, long));
	else if (pf->flags & LL_MODIFIER)
		return (va_arg(pf->ap, long long));
	else if (pf->flags & J_MODIFIER)
		return (va_arg(pf->ap, intmax_t));
	else if (pf->flags & Z_MODIFIER)
		return (va_arg(pf->ap, ssize_t));
	else
		return (va_arg(pf->ap, int));
}

unsigned long long	pf_uvalue(t_pf *pf)
{
	if (pf->flags & HH_MODIFIER)
		return (unsigned char)(va_arg(pf->ap, unsigned int));
	else if (pf->flags & H_MODIFIER)
		return (unsigned short)(va_arg(pf->ap, unsigned int));
	else if (pf->flags & L_MODIFIER)
		return (va_arg(pf->ap, unsigned long));
	else if (pf->flags & LL_MODIFIER)
		return (va_arg(pf->ap, unsigned long long));
	else if (pf->flags & J_MODIFIER)
		return (va_arg(pf->ap, uintmax_t));
	else if (pf->flags & Z_MODIFIER)
		return (va_arg(pf->ap, size_t));
	else
		return (va_arg(pf->ap, unsigned int));
}
