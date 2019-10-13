/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 22:50:17 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/13 16:14:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <setjmp.h>
#include <stdio.h>
#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include "error.h"

static jmp_buf			jmp_parser;
static const char		*jmp_message;

static ast_node_t		*parse_expr(lexeme_t **current);

static void				throw_error(int type, const char *reason)
{
	jmp_message = reason;
	longjmp(jmp_parser, type);
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

static ast_node_t		*parse_pow(lexeme_t **current)
{
	ast_node_t	*node = NULL;

	if (is_lexeme_type(current, e_LEX_POW))
	{
		accept_lexeme(current, e_LEX_POW);
		node = parse_expr(current);
		if (node == NULL)
			throw_error(JUMP_PARSE_ERROR, "expr");
	}
	return node;
}

static ast_node_t		*parse_factor(lexeme_t **current)
{
	ast_node_t	*node = NULL;

	if (is_lexeme_type(current, e_LEX_VAR | e_LEX_NUMBER))
	{
		node = create_node(*current, NULL, NULL);
		accept_lexeme(current, get_lexeme_type(current));
	}
	else if (is_lexeme_type(current, e_LEX_OPEN_BRACKET))
	{
		accept_lexeme(current, e_LEX_OPEN_BRACKET);
		node = parse_expr(current);
		if (!accept_lexeme(current, e_LEX_CLOSE_BRACKET))
			throw_error(JUMP_PARSE_ERROR, "close bracket");
	}
	if (node != NULL && is_lexeme_type(current, e_LEX_POW))
		node = create_node(*current, node, parse_pow(current));
	return node;
}

static ast_node_t		*parse_term(lexeme_t **current)
{
	ast_node_t	*node = parse_factor(current);
	lexeme_t	*token;

	if (node == NULL)
		throw_error(JUMP_PARSE_ERROR, "factor");
	while (is_lexeme_type(current, e_LEX_OP_MUL | e_LEX_OP_DIV))
	{
		token = *current;
		accept_lexeme(current, e_LEX_OP_MUL | e_LEX_OP_DIV);
		node = create_node(token, node, parse_factor(current));
	}
	return node;
}

static ast_node_t		*parse_expr(lexeme_t **current)
{
	ast_node_t	*node = parse_term(current);
	lexeme_t	*token;

	if (node == NULL)
		throw_error(JUMP_PARSE_ERROR, "term");
	while (is_lexeme_type(current, e_LEX_OP_PLUS | e_LEX_OP_MINUS))
	{
		token = *current;
		accept_lexeme(current, e_LEX_OP_PLUS | e_LEX_OP_MINUS);
		node = create_node(token, node, parse_term(current));
	}
	return node;
}

static void				parse_poly(lexeme_t **current, ast_node_t *root)
{
	root->left = parse_expr(current);
	if (root->left == NULL)
		throw_error(JUMP_PARSE_ERROR, "poly");
	else if (!accept_lexeme(current, e_LEX_EQUAL))
		throw_error(JUMP_PARSE_ERROR, "=");
	root->right = parse_expr(current);
	if (root->right == NULL)
		throw_error(JUMP_PARSE_ERROR, "poly result");
	else if (!accept_lexeme(current, e_LEX_END))
		throw_error(JUMP_PARSE_ERROR, "poly end");
}

int						parse_lexemes(lexeme_list_t *lst)
{
	ast_node_t	*root = calloc(1, sizeof(ast_node_t));
	lexeme_t	*node = lst->front;
	int			ret;

	ret = setjmp(jmp_parser);
	switch (ret)
	{
		case JUMP_NO_ERROR:
			if (root == NULL)
				throw_error(JUMP_UNEXPECTED, "unexpected error");
			parse_poly(&node, root);
			return 1;
		case JUMP_PARSE_ERROR:
			del_ast(root);
			print_parser_error(lst, node, jmp_message);
			break;
		case JUMP_UNEXPECTED:
		default:
			del_ast(root);
			fprintf(stderr, "%s\n", jmp_message);
			break;
	}
	return 0;
}
