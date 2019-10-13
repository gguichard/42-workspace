/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 11:40:28 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/13 15:31:28 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "lexer.h"

typedef enum
{
	e_AST_UNKNOWN = 0,
	e_AST_NUMBER = 1,
	e_AST_VAR = 2,
	e_AST_POW = 4,
	e_AST_EQUAL = 8,
	e_AST_OP_PLUS = 16,
	e_AST_OP_MINUS = 32,
	e_AST_OP_DIV = 64,
	e_AST_OP_MUL = 128
} ast_node_type_t;

typedef struct	ast_node
{
	lexeme_t		*token;
	struct ast_node	*left;
	struct ast_node	*right;
} ast_node_t;

void			del_ast(ast_node_t *root);

#endif
