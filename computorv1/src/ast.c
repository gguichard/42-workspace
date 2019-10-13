/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 12:48:10 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/13 15:31:02 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast.h"

void	del_ast(ast_node_t *root)
{
	if (root != NULL)
	{
		del_ast(root->left);
		del_ast(root->right);
		free(root);
	}
}
