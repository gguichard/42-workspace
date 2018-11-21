/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 09:05:16 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/21 16:16:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

static int	parse_flag(t_token *tk, const char **p_str)
{
	if ((*p_str)[0] == '#')
		tk->flags |= HASH_FLAG;
	else if ((*p_str)[0] == '0')
		tk->flags |= ZERO_FLAG;
	else if ((*p_str)[0] == '-')
		tk->flags |= MINUS_FLAG;
	else if ((*p_str)[0] == ' ')
		tk->flags |= SPACE_FLAG;
	else if ((*p_str)[0] == '+')
		tk->flags |= PLUS_FLAG;
	else
		return (0);
	(*p_str)++;
	return (1);
}

static int	parse_modifier(t_token *tk, const char **p_str)
{
	if ((*p_str)[0] == 'z')
	{
		tk->modifiers |= Z_MODIFIER;
		(*p_str)++;
		return (1);
	}
	else if ((*p_str)[0] == 'h')
	{
		if ((*p_str)[1] != 'h')
			tk->modifiers |= H_MODIFIER;
		else
		{
			(*p_str)++;
			tk->modifiers |= HH_MODIFIER;
		}
		(*p_str)++;
		return (1);
	}
	else if ((*p_str)[0] == 'l')
	{
		if ((*p_str)[1] != 'l')
			tk->modifiers |= L_MODIFIER;
		else
		{
			(*p_str)++;
			tk->modifiers |= LL_MODIFIER;
		}
		(*p_str)++;
		return (1);
	}
	return (0);
}

static int	parse_width_field(t_token *tk, const char **p_str)
{
	if ((*p_str)[0] >= '0' && (*p_str)[0] <= '9')
	{
		tk->width_field = ft_simple_atoi(p_str);
		return (1);
	}
	else if ((*p_str)[0] == '*')
	{
		(*p_str)++;
		tk->width_field = -1;
		tk->wildcards |= WIDTH_WILDCARD;
		return (1);
	}
	return (0);
}

static int	parse_precision(t_token *tk, const char **p_str)
{
	if ((*p_str)[0] == '.')
	{
		(*p_str)++;
		if ((*p_str)[0] != '*')
			tk->precision = ft_simple_atoi(p_str);
		else
		{
			(*p_str)++;
			tk->precision = -1;
			tk->wildcards |= PRECISION_WILDCARD;
		}
		return (1);
	}
	return (0);
}

int			tk_parse(t_token *tk, const char *str)
{
	const char	*start;

	start = str;
	tk->width_field = -1;
	tk->precision = -1;
	tk->flags = 0;
	tk->modifiers = 0;
	tk->wildcards = 0;
	tk->type = 0;
	while (parse_flag(tk, &str)
		|| parse_modifier(tk, &str)
		|| parse_width_field(tk, &str)
		|| parse_precision(tk, &str))
		continue ;
	tk->type = *str;
	return (int)(str - start);
}
