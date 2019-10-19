/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 12:48:10 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/18 11:41:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include "utils.h"

void		free_ast(ast_node_t *root)
{
	if (root != NULL)
	{
		free_ast(root->left);
		free_ast(root->right);
		free(root);
	}
}

static void	print_ast_depth(ast_node_t *node, size_t depth, ast_node_t *target)
{
	if (node != NULL)
	{
		if (node == target)
			fprintf(stdout, "\e[33;1m");
		print_ast_depth(node->left, depth + 1, target);
		fprintf_char_n_times(stdout, '\t', depth);
		fprintf(stdout, "%.*s\n"
			, (int)node->token->content_size, node->token->content);
		print_ast_depth(node->right, depth + 1, target);
		if (node == target)
			fprintf(stdout, "\e[0m");
	}
}

void		print_ast(ast_node_t *node)
{
	ast_node_t	*root = node;

	while (root->parent != NULL)
		root = root->parent;
	print_ast_depth(root, 0, node);
}
