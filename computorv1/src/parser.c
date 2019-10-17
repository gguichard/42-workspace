/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 22:50:17 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/17 15:53:02 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <setjmp.h>
#include <stdio.h>
#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include "alloc_list.h"
#include "error.h"
#include "utils.h"

static jmp_error_t		error;
static alloc_list_t		*alloc_lst;
static lexeme_t			lexeme_ope_mul = {
	.type = e_LEX_OPE_MUL,
	.content = "*",
	.content_size = 1,
	.next = NULL
};

static ast_node_t		*parse_expr(lexeme_t **current, int allow_var);

static void				throw_error(const char *reason)
{
	error.message = reason;
	longjmp(error.buf, JUMP_PARSE_ERROR);
}

static ast_node_t		*create_node(lexeme_t *token
	, ast_node_t *left, ast_node_t *right)
{
	ast_node_t	*node = malloc(sizeof(ast_node_t));

	if (node == NULL)
		exit_unexpected();
	node->left = left;
	node->right = right;
	node->token = token;
	push_alloc(&alloc_lst, node);
	return node;
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

static ast_node_t		*parse_factor(lexeme_t **current, int allow_var)
{
	ast_node_t	*node = NULL;
	lexeme_t	*token;
	ast_node_t	*expr;

	if (!allow_var && is_lexeme_type(current, e_LEX_VAR))
		throw_error("variable not allowed in power factor");
	else if (is_lexeme_type(current, e_LEX_VAR | e_LEX_NUMBER))
	{
		node = create_node(*current, NULL, NULL);
		accept_lexeme(current, get_lexeme_type(current));
	}
	else if (is_lexeme_type(current, e_LEX_OPE_PLUS | e_LEX_OPE_MINUS))
	{
		token = *current;
		accept_lexeme(current, get_lexeme_type(current));
		node = parse_factor(current, allow_var);
		if (node == NULL)
			throw_error("expected factor after unary operator");
		node = create_node(token, NULL, node);
	}
	else if (is_lexeme_type(current, e_LEX_OPEN_BRACKET))
	{
		accept_lexeme(current, e_LEX_OPEN_BRACKET);
		node = parse_expr(current, allow_var);
		if (node == NULL)
			throw_error("expected expr inside brackets");
		else if (!accept_lexeme(current, e_LEX_CLOSE_BRACKET))
			throw_error("expected close bracket");
	}
	if (node != NULL && is_lexeme_type(current, e_LEX_OPE_POW))
	{
		token = *current;
		accept_lexeme(current, e_LEX_OPE_POW);
		expr = parse_factor(current, 0);
		if (expr == NULL)
			throw_error("expected power factor");
		node = create_node(token, node, expr);
	}
	return node;
}

static ast_node_t		*parse_term(lexeme_t **current, int allow_var)
{
	ast_node_t	*node = parse_factor(current, allow_var);
	ast_node_t	*factor;
	lexeme_t	*token;

	while (is_lexeme_type(current
		, e_LEX_OPE_MUL | e_LEX_OPE_DIV | e_LEX_VAR | e_LEX_OPEN_BRACKET))
	{
		if (node == NULL)
			throw_error("term must begin with a factor");
		else if (is_lexeme_type(current, e_LEX_VAR | e_LEX_OPEN_BRACKET))
			token = &lexeme_ope_mul;
		else
			token = *current;
		accept_lexeme(current, e_LEX_OPE_MUL | e_LEX_OPE_DIV);
		factor = parse_factor(current, allow_var);
		if (factor == NULL)
			throw_error("expected factor");
		node = create_node(token, node, factor);
	}
	return node;
}

static ast_node_t		*parse_expr(lexeme_t **current, int allow_var)
{
	ast_node_t	*node = parse_term(current, allow_var);
	ast_node_t	*term;
	lexeme_t	*token;

	while (is_lexeme_type(current, e_LEX_OPE_PLUS | e_LEX_OPE_MINUS))
	{
		if (node == NULL)
			throw_error("expr must begin with a factor");
		token = *current;
		accept_lexeme(current, e_LEX_OPE_PLUS | e_LEX_OPE_MINUS);
		term = parse_term(current, allow_var);
		if (term == NULL)
			throw_error("expected term");
		node = create_node(token, node, term);
	}
	return node;
}

static void				parse_poly(lexeme_t **current, ast_node_t *root)
{
	root->left = parse_expr(current, 1);
	if (root->left == NULL)
		throw_error("expected left expr");
	else if (!is_lexeme_type(current, e_LEX_EQUAL))
		throw_error("expected equal");
	root->token = *current;
	accept_lexeme(current, e_LEX_EQUAL);
	root->right = parse_expr(current, 1);
	if (root->right == NULL)
		throw_error("expected right expr");
	else if (!accept_lexeme(current, e_LEX_END))
		throw_error("expected poly end");
}

ast_node_t				*parse_lexemes(lexeme_list_t *lst)
{
	ast_node_t	*root = NULL;
	lexeme_t	*node = lst->front;
	int			ret;

	ret = setjmp(error.buf);
	switch (ret)
	{
		case JUMP_NO_ERROR:
			root = create_node(NULL, NULL, NULL);
			parse_poly(&node, root);
			del_alloc_list(&alloc_lst, NULL);
			return root;
		case JUMP_PARSE_ERROR:
		default:
			del_alloc_list(&alloc_lst, free);
			print_parser_error(lst, node, error.message);
			break;
	}
	return NULL;
}
