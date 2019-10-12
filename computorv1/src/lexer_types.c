/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:36:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/10 15:07:29 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "lexer.h"

void	lex_bracket(lexeme_ctx_t *ctx)
{
	if (strchr("([", ctx->buffer[0]) != NULL)
		ctx->type = e_LEX_OPEN_BRACKET;
	else
		ctx->type = e_LEX_CLOSE_BRACKET;
}

void	lex_operator(lexeme_ctx_t *ctx)
{
	switch (ctx->buffer[0])
	{
		case '+':
			ctx->type = e_LEX_OP_PLUS;
			break;
		case '-':
			ctx->type = e_LEX_OP_MINUS;
			break;
		case '/':
			ctx->type = e_LEX_OP_DIV;
			break;
		case '*':
			ctx->type = e_LEX_OP_MUL;
			break;
		default:
			ctx->type = e_LEX_UNKNOWN;
			break;
	}
}

void	lex_number(lexeme_ctx_t *ctx)
{
	while (ctx->buffer[ctx->len] != '\0' &&
		strchr(DIGIT_CHARS, ctx->buffer[ctx->len]) != NULL)
		ctx->len += 1;
	ctx->type = e_LEX_NUMBER;
}

void	lex_var(lexeme_ctx_t *ctx)
{
	ctx->type = e_LEX_VAR;
}

void	lex_pow(lexeme_ctx_t *ctx)
{
	ctx->type = e_LEX_POW;
}

void	lex_equal(lexeme_ctx_t *ctx)
{
	ctx->type = e_LEX_EQUAL;
}
