/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:58:59 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/17 12:18:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "utils.h"

static lexeme_ctx_t	lexeme_end_ctx = {
	.type = e_LEX_END,
	.buffer = " ",
	.len = 1
};

static lexeme_ctx_t	dispatch_lexer(const char *str, size_t offset)
{
	static lexer_dispatch_t	dispatch[] = {
		{BRACKET_CHARS, lex_bracket},
		{OPERATOR_CHARS, lex_operator},
		{DIGIT_CHARS, lex_number},
		{VAR_CHARS, lex_var},
		{EQUAL_CHARS, lex_equal}
	};
	size_t			idx;
	lexeme_ctx_t	ctx = {
		.type = e_LEX_UNKNOWN,
		.buffer = &str[offset],
		.len = 1
	};

	for (idx = 0; idx < (sizeof(dispatch) / sizeof(dispatch[0])); idx++)
	{
		if (strchr(dispatch[idx].allowed_chars, str[offset]) != NULL)
		{
			dispatch[idx].fn(&ctx);
			break;
		}
	}
	return ctx;
}

static void			store_lexeme(lexeme_list_t *lst, lexeme_ctx_t *ctx)
{
	lexeme_t	*node;

	if (ctx->type == e_LEX_UNKNOWN && lst->back != NULL
		&& lst->back->type == e_LEX_UNKNOWN)
	{
		// Rassemblement des tokens UNKNOWN
		node = lst->back;
		node->content_size += ctx->len;
	}
	else
	{
		node = malloc(sizeof(lexeme_t));
		if (node == NULL)
			exit_unexpected();
		node->type = ctx->type;
		node->content = ctx->buffer;
		node->content_size = ctx->len;
		node->next = NULL;
		if (lst->front == NULL)
			lst->front = node;
		if (lst->back != NULL)
			lst->back->next = node;
		lst->back = node;
	}
}

void				free_lexeme_list(lexeme_list_t *lst)
{
	lexeme_t	*node;
	lexeme_t	*next;

	for (node = lst->front; node != NULL; node = next)
	{
		next = node->next;
		free(node);
	}
	lst->front = NULL;
	lst->back = NULL;
}

lexeme_list_t		split_input_in_lexemes(const char *str)
{
	size_t			offset = 0;
	lexeme_ctx_t	ctx;
	lexeme_list_t	lst = {.front = NULL, .back = NULL};

	while (str[offset] != '\0')
	{
		if (strchr(WHITESPACE_CHARS, str[offset]))
			offset += 1;
		else
		{
			ctx = dispatch_lexer(str, offset);
			store_lexeme(&lst, &ctx);
			offset += ctx.len;
		}
	}
	store_lexeme(&lst, &lexeme_end_ctx);
	return lst;
}
