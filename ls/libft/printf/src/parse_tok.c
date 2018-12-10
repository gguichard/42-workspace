/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 21:21:03 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/09 20:58:11 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

int	pf_flag(t_pf *pf, const char **tok)
{
	if (**tok == '#')
		pf->flags |= HASH_FLAG;
	else if (**tok == '0' && !(pf->flags & MINUS_FLAG))
		pf->flags |= ZERO_FLAG;
	else if (**tok == ' ' && !(pf->flags & PLUS_FLAG))
		pf->flags |= SPACE_FLAG;
	else if (**tok == '-')
	{
		pf->flags &= ~ZERO_FLAG;
		pf->flags |= MINUS_FLAG;
	}
	else if (**tok == '+')
	{
		pf->flags &= ~SPACE_FLAG;
		pf->flags |= PLUS_FLAG;
	}
	(*tok)++;
	return (1);
}

int	pf_modifier(t_pf *pf, const char **tok)
{
	pf->flags &= ~(LUP_MODIFIER | J_MODIFIER | Z_MODIFIER
			| H_MODIFIER | L_MODIFIER | HH_MODIFIER | LL_MODIFIER);
	if ((*tok)[0] == 'L')
		pf->flags |= LUP_MODIFIER;
	else if ((*tok)[0] == 'j')
		pf->flags |= J_MODIFIER;
	else if ((*tok)[0] == 'z')
		pf->flags |= Z_MODIFIER;
	else if ((*tok)[0] == 'h' && (*tok)[1] != 'h')
		pf->flags |= H_MODIFIER;
	else if ((*tok)[0] == 'l' && (*tok)[1] != 'l')
		pf->flags |= L_MODIFIER;
	else if ((*tok)[0] == 'h' || (*tok)[0] == 'l')
	{
		(*tok)++;
		pf->flags |= (*tok)[0] == 'h' ? HH_MODIFIER : LL_MODIFIER;
	}
	(*tok)++;
	return (1);
}

int	pf_precision(t_pf *pf, const char **tok)
{
	(*tok)++;
	if (**tok != '*')
		pf->precision = ft_simple_atoi(tok);
	else
	{
		(*tok)++;
		pf->precision = -1;
		pf->flags |= PRECISION_WILDCARD;
	}
	return (1);
}

int	pf_w_field(t_pf *pf, const char **tok)
{
	if (**tok != '*')
		pf->w_field = ft_simple_atoi(tok);
	else
	{
		(*tok)++;
		pf->w_field = -1;
		pf->flags |= WIDTH_WILDCARD;
	}
	return (1);
}
