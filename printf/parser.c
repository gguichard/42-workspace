/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 09:05:16 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/21 19:31:06 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

static int	parse_flag(t_token *tok, const char **p_str)
{
	if ((*p_str)[0] == '#')
		tok->flags |= HASH_FLAG;
	else if ((*p_str)[0] == '0')
		tok->flags |= ZERO_FLAG;
	else if ((*p_str)[0] == '-')
		tok->flags |= MINUS_FLAG;
	else if ((*p_str)[0] == ' ')
		tok->flags |= SPACE_FLAG;
	else if ((*p_str)[0] == '+')
		tok->flags |= PLUS_FLAG;
	else
		return (0);
	(*p_str)++;
	return (1);
}

static int	parse_modifier(t_token *tok, const char **p_str)
{
	if ((*p_str)[0] == 'z')
		tok->modifiers |= Z_MODIFIER;
	else if ((*p_str)[0] == 'h')
	{
		if ((*p_str)[1] != 'h')
			tok->modifiers |= H_MODIFIER;
		else
		{
			(*p_str)++;
			tok->modifiers |= HH_MODIFIER;
		}
	}
	else if ((*p_str)[0] == 'l')
	{
		if ((*p_str)[1] != 'l')
			tok->modifiers |= L_MODIFIER;
		else
		{
			(*p_str)++;
			tok->modifiers |= LL_MODIFIER;
		}
	}
	else
		return (0);
	(*p_str)++;
	return (1);
}

static int	parse_width_field(t_token *tok, const char **p_str)
{
	if ((*p_str)[0] >= '0' && (*p_str)[0] <= '9')
	{
		tok->width_field = ft_simple_atoi(p_str);
		return (1);
	}
	else if ((*p_str)[0] == '*')
	{
		(*p_str)++;
		tok->width_field = -1;
		tok->wildcards |= WIDTH_WILDCARD;
		return (1);
	}
	return (0);
}

static int	parse_precision(t_token *tok, const char **p_str)
{
	if ((*p_str)[0] == '.')
	{
		(*p_str)++;
		if ((*p_str)[0] != '*')
			tok->precision = ft_simple_atoi(p_str);
		else
		{
			(*p_str)++;
			tok->precision = -1;
			tok->wildcards |= PRECISION_WILDCARD;
		}
		return (1);
	}
	return (0);
}

int			tk_parse(t_token *tok, const char *str)
{
	const char	*start;

	start = str;
	tok->width_field = -1;
	tok->precision = -1;
	tok->flags = 0;
	tok->modifiers = 0;
	tok->wildcards = 0;
	tok->type = 0;
	while (parse_flag(tok, &str)
		|| parse_modifier(tok, &str)
		|| parse_width_field(tok, &str)
		|| parse_precision(tok, &str))
		continue ;
	tok->type = *str;
	return (int)(str - start);
}
