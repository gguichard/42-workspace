/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:36:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/17 10:27:29 by gguichar         ###   ########.fr       */
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
			ctx->type = e_LEX_OPE_PLUS;
			break;
		case '-':
			ctx->type = e_LEX_OPE_MINUS;
			break;
		case '/':
			ctx->type = e_LEX_OPE_DIV;
			break;
		case '*':
			if (ctx->buffer[1] != '*')
				ctx->type = e_LEX_OPE_MUL;
			else
			{
				ctx->len += 1;
				ctx->type = e_LEX_OPE_POW;
			}
			break;
		case '^':
			ctx->type = e_LEX_OPE_POW;
			break;
		default:
			ctx->type = e_LEX_UNKNOWN;
			break;
	}
}

void	lex_number(lexeme_ctx_t *ctx)
{
	int	decimal = 0;

	while (ctx->buffer[ctx->len] != '\0'
		&& (ctx->buffer[ctx->len] == '.'
			|| strchr(DIGIT_CHARS, ctx->buffer[ctx->len]) != NULL))
	{
		if (ctx->buffer[ctx->len] == '.')
			decimal += 1;
		if (decimal > 1)
			break;
		ctx->len += 1;
	}
	ctx->type = e_LEX_NUMBER;
}

void	lex_var(lexeme_ctx_t *ctx)
{
	ctx->type = e_LEX_VAR;
}

void	lex_equal(lexeme_ctx_t *ctx)
{
	ctx->type = e_LEX_EQUAL;
}
