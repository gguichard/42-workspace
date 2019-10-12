/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 22:50:17 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/12 21:25:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <setjmp.h>
#include "parser.h"
#include "lexer.h"
#include "error.h"

static jmp_buf			s_jmp_parser;
static const char		*s_jmp_message;
static int				parse_expr(lexeme_t **current);

static void				throw_parser_error(const char *reason)
{
	s_jmp_message = reason;
	longjmp(s_jmp_parser, 1);
}

static lexeme_type_t	get_lexeme_type(lexeme_t **current)
{
	lexeme_t	*node = *current;

	if (node == NULL)
		return e_LEX_UNKNOWN;
	return node->type;
}

static int				is_lexeme_type(lexeme_t **current, lexeme_type_t type)
{
	return get_lexeme_type(current) & type;
}

static int				accept_lexeme(lexeme_t **current, lexeme_type_t type)
{
	lexeme_t	*node = *current;

	if (is_lexeme_type(current, type))
	{
		*current = node->next;
		return 1;
	}
	return 0;
}

static int				parse_factor(lexeme_t **current)
{
	int	ret = 0;

	if (is_lexeme_type(current, e_LEX_VAR | e_LEX_NUMBER))
		ret = accept_lexeme(current, get_lexeme_type(current));
	else if (is_lexeme_type(current, e_LEX_OPEN_BRACKET))
	{
		accept_lexeme(current, e_LEX_OPEN_BRACKET);
		ret = parse_expr(current);
		if (ret && !accept_lexeme(current, e_LEX_CLOSE_BRACKET))
			throw_parser_error("close bracket");
	}
	if (ret && accept_lexeme(current, e_LEX_POW) && !parse_expr(current))
		throw_parser_error("expr");
	return ret;
}

static int				parse_term(lexeme_t **current)
{
	if (!parse_factor(current))
		return 0;
	while (is_lexeme_type(current, e_LEX_OP_MUL | e_LEX_OP_DIV | e_LEX_VAR))
	{
		if (is_lexeme_type(current, e_LEX_OP_MUL | e_LEX_OP_DIV))
			*current = (*current)->next;
		if (!parse_factor(current))
			throw_parser_error("factor");
	}
	return 1;
}

static int				parse_expr(lexeme_t **current)
{
	if (!parse_term(current))
		return 0;
	while (is_lexeme_type(current, e_LEX_OP_PLUS | e_LEX_OP_MINUS))
	{
		*current = (*current)->next;
		if (!parse_term(current))
			throw_parser_error("term");
	}
	return 1;
}

static int				parse_poly(lexeme_t **current)
{
	if (!parse_expr(current))
		throw_parser_error("poly");
	else if (!accept_lexeme(current, e_LEX_EQUAL))
		throw_parser_error("=");
	else if (!parse_expr(current))
		throw_parser_error("poly result");
	return 1;
}

int						parse_lexemes(lexeme_list_t *lst)
{
	lexeme_t	*node = lst->front;

	if (!setjmp(s_jmp_parser))
		return parse_poly(&node) && accept_lexeme(&node, e_LEX_END);
	else
	{
		print_parser_error(lst, node, s_jmp_message);
		return 0;
	}
}
