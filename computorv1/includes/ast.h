/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 11:40:28 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/18 11:59:43 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "lexer.h"

typedef struct ast_node
{
	lexeme_t		*token;
	struct ast_node	*left;
	struct ast_node	*right;
	struct ast_node	*parent;
} ast_node_t;

void	free_ast(ast_node_t *root);
void	print_ast(ast_node_t *node);

#endif
