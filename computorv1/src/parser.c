/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 22:50:17 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/15 18:51:29 by gguichar         ###   ########.fr       */
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

static jmp_error_t		error;
static alloc_list_t		*alloc_lst;

static ast_node_t		*parse_expr(lexeme_t **current, int allow_var);

static void				throw_error(int type, const char *reason)
{
	error.message = reason;
	longjmp(error.buf, type);
}

static ast_node_t		*create_node(lexeme_t *token
	, ast_node_t *left, ast_node_t *right)
{
	ast_node_t	*node = malloc(sizeof(ast_node_t));

	if (node == NULL)
		throw_error(JUMP_UNEXPECTED, "unexpected error");
	node->left = left;
	node->right = right;
	node->token = token;
	if (!push_alloc(&alloc_lst, node))
	{
		free(node);
		throw_error(JUMP_UNEXPECTED, "unexpected error");
	}
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
		throw_error(JUMP_PARSE_ERROR, "variable not allowed in power factor");
	else if (is_lexeme_type(current, e_LEX_VAR | e_LEX_NUMBER))
	{
		node = create_node(*current, NULL, NULL);
		accept_lexeme(current, get_lexeme_type(current));
	}
	else if (is_lexeme_type(current, e_LEX_OPEN_BRACKET))
	{
		accept_lexeme(current, e_LEX_OPEN_BRACKET);
		node = parse_expr(current, allow_var);
		if (node == NULL)
			throw_error(JUMP_PARSE_ERROR, "expected expr inside brackets");
		else if (!accept_lexeme(current, e_LEX_CLOSE_BRACKET))
			throw_error(JUMP_PARSE_ERROR, "expected close bracket");
	}
	if (node != NULL && is_lexeme_type(current, e_LEX_OP_POW))
	{
		token = *current;
		accept_lexeme(current, e_LEX_OP_POW);
		expr = parse_factor(current, 0);
		if (expr == NULL)
			throw_error(JUMP_PARSE_ERROR, "expected power factor");
		node = create_node(token, node, expr);
	}
	return node;
}

static ast_node_t		*parse_term(lexeme_t **current, int allow_var)
{
	ast_node_t	*node = parse_factor(current, allow_var);
	ast_node_t	*factor;
	lexeme_t	*token;

	while (is_lexeme_type(current, e_LEX_OP_MUL | e_LEX_OP_DIV))
	{
		if (node == NULL)
			throw_error(JUMP_PARSE_ERROR, "term must begin with a factor");
		token = *current;
		accept_lexeme(current, e_LEX_OP_MUL | e_LEX_OP_DIV);
		factor = parse_factor(current, allow_var);
		if (factor == NULL)
			throw_error(JUMP_PARSE_ERROR, "expected factor");
		node = create_node(token, node, factor);
	}
	return node;
}

static ast_node_t		*parse_expr(lexeme_t **current, int allow_var)
{
	ast_node_t	*node = parse_term(current, allow_var);
	ast_node_t	*term;
	lexeme_t	*token;

	while (is_lexeme_type(current, e_LEX_OP_PLUS | e_LEX_OP_MINUS))
	{
		if (node == NULL)
			throw_error(JUMP_PARSE_ERROR, "expr must begin with a factor");
		token = *current;
		accept_lexeme(current, e_LEX_OP_PLUS | e_LEX_OP_MINUS);
		term = parse_term(current, allow_var);
		if (term == NULL)
			throw_error(JUMP_PARSE_ERROR, "expected term");
		node = create_node(token, node, term);
	}
	return node;
}

static void				parse_poly(lexeme_t **current, ast_node_t *root)
{
	root->left = parse_expr(current, 1);
	if (root->left == NULL)
		throw_error(JUMP_PARSE_ERROR, "expected left expr");
	else if (!is_lexeme_type(current, e_LEX_EQUAL))
		throw_error(JUMP_PARSE_ERROR, "expected equal");
	root->token = *current;
	accept_lexeme(current, e_LEX_EQUAL);
	root->right = parse_expr(current, 1);
	if (root->right == NULL)
		throw_error(JUMP_PARSE_ERROR, "expected right expr");
	else if (!accept_lexeme(current, e_LEX_END))
		throw_error(JUMP_PARSE_ERROR, "expected poly end");
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
			del_alloc_list(&alloc_lst, free);
			print_parser_error(lst, node, error.message);
			break;
		case JUMP_UNEXPECTED:
		default:
			del_alloc_list(&alloc_lst, free);
			fprintf(stderr, "%s\n", error.message);
			break;
	}
	return NULL;
}
