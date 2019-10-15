/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 12:48:10 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/14 13:41:21 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast.h"

void	free_ast(ast_node_t *root)
{
	if (root != NULL)
	{
		free_ast(root->left);
		free_ast(root->right);
		free(root);
	}
}
