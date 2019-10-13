/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:04:44 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/12 23:00:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <string.h>

# define WHITESPACE_CHARS " \t"
# define BRACKET_CHARS "()[]"
# define OPERATOR_CHARS "+-*/"
# define DIGIT_CHARS "0123456789"
# define VAR_CHARS "xX"
# define POW_CHARS "^"
# define EQUAL_CHARS "="

typedef enum
{
	e_LEX_UNKNOWN = 0,
	e_LEX_OPEN_BRACKET = 1,
	e_LEX_CLOSE_BRACKET = 2,
	e_LEX_NUMBER = 4,
	e_LEX_VAR = 8,
	e_LEX_POW = 16,
	e_LEX_EQUAL = 32,
	e_LEX_OP_PLUS = 64,
	e_LEX_OP_MINUS = 128,
	e_LEX_OP_DIV = 256,
	e_LEX_OP_MUL = 512,
	e_LEX_END = 1024
} lexeme_type_t;

typedef struct lexeme
{
	lexeme_type_t	type;
	const char		*content;
	size_t			content_size;
	struct lexeme	*next;
} lexeme_t;

typedef struct
{
	lexeme_type_t	type;
	const char		*buffer;
	size_t			len;
} lexeme_ctx_t;

typedef struct
{
	lexeme_t		*front;
	lexeme_t		*back;
} lexeme_list_t;

typedef struct
{
	const char	*allowed_chars;
	void		(*fn)(lexeme_ctx_t *);
} lexer_dispatch_t;

void			lex_bracket(lexeme_ctx_t *ctx);
void			lex_operator(lexeme_ctx_t *ctx);
void			lex_number(lexeme_ctx_t *ctx);
void			lex_var(lexeme_ctx_t *ctx);
void			lex_pow(lexeme_ctx_t *ctx);
void			lex_equal(lexeme_ctx_t *ctx);

void			free_lexeme_list(lexeme_list_t *lst);
lexeme_list_t	split_input_in_lexemes(const char *str);

#endif
