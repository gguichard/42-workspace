/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 13:59:21 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/22 13:11:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "libft.h"

static void	pad_fieldprecision(t_token *tok, t_intstuff *vars)
{
	if (tok->precision > 0 && tok->buf.size < tok->precision)
	{
		buf_pad(&(tok->buf), '0', tok->precision, 0);
		if (!(tok->buf.str))
			exit(1);
	}
	vars->can_expand = tok->precision < 0
		&& tok->flags & ZERO_FLAG && !(tok->flags & MINUS_FLAG);
	if (tok->width_field > 0 && vars->can_expand)
	{
		vars->offset = 0;
		if ((tok->type == 'd' || tok->type == 'i')
			&& (vars->neg || tok->flags & PLUS_FLAG || tok->flags & SPACE_FLAG))
			vars->offset += 1;
		else if (tok->flags & HASH_FLAG && tok->type == 'o'
			&& (!(vars->is_zero) || tok->precision == 0))
			vars->offset += 1;
		else if (tok->flags & HASH_FLAG && ft_tolower(tok->type) == 'x'
			&& !(vars->is_zero))
			vars->offset += 2;
		buf_pad(&(tok->buf), '0', tok->width_field - vars->offset, 0);
		if (!(tok->buf.str))
			exit(1);
	}
}

static void	prepend_stuff(t_token *tok, t_intstuff *vars)
{
	pad_fieldprecision(tok, vars);
	if ((tok->type == 'd' || tok->type == 'i'))
	{
		if (vars->neg)
			buf_prepend("-", &(tok->buf));
		else if (tok->flags & PLUS_FLAG)
			buf_prepend("+", &(tok->buf));
		else if (tok->flags & SPACE_FLAG)
			buf_prepend(" ", &(tok->buf));
		if (!(tok->buf.str))
			exit(1);
	}
	if (tok->flags & HASH_FLAG)
	{
		if (tok->type == 'o'
			&& ((tok->buf.str)[0] != '0' || tok->precision == 0))
			buf_prepend("0", &(tok->buf));
		else if ((tok->type == 'x' || tok->type == 'X') && !(vars->is_zero))
			buf_prepend("0X", &(tok->buf));
		if (!(tok->buf.str))
			exit(1);
	}
}

void		convert_int(t_token *tok, va_list ap)
{
	t_intstuff	vars;

	vars.neg = intval_to_buf(tok, ap);
	if (!(tok->buf.str))
		exit(1);
	tok->buf.size = ft_strlen(tok->buf.str);
	vars.is_zero = tok->buf.size == 0
		|| (tok->buf.size == 1 && (tok->buf.str)[0] == '0');
	prepend_stuff(tok, &vars);
	if (tok->type == 'x')
		tok->buf.str = ft_strtolower(tok->buf.str);
	if (tok->width_field > 0
		&& tok->buf.size < tok->width_field && !(vars.can_expand))
		buf_pad(&(tok->buf), ' ', tok->width_field, tok->flags & MINUS_FLAG);
}
