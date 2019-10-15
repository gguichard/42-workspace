/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:03:18 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/15 21:10:01 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "computorv1.h"
#include "ast.h"

static void	reorder_poly_factors(factor_list_t **lst)
{
	factor_list_t	*node;
	factor_list_t	*next, *prev = NULL;

	for (node = *lst; node != NULL && node->next != NULL; node = next)
	{
		next = node->next;
		if (next->power > node->power)
		{
			if (prev == NULL)
				*lst = next;
			else
				prev->next = next;
			node->next = next->next;
			next->next = node;
			prev = NULL;
			next = *lst;
		}
		else
			prev = node;
	}
}

static int	get_poly_degree(factor_list_t *lst)
{
	int				degree = 0;
	factor_list_t	*node;

	for (node = lst; node != NULL; node = node->next)
	{
		if (node->power < 0 || degree < node->power)
			degree = node->power;
	}
	return degree;
}

void		solve_poly(ast_node_t *root)
{
	factor_list_t	*poly;
	factor_list_t	*result;
	int				degree;

	poly = compute_ast_factors(root->left);
	result = compute_ast_factors(root->right);
	reduce_factor_list(&poly, result);
	reorder_poly_factors(&poly);
	fprintf(stdout, "Reduced form: ");
	print_factors(poly);
	fprintf(stdout, " = 0\n");
	degree = get_poly_degree(poly);
	fprintf(stdout, "Polynomial degree: %d\n", degree);
	if (!solve_poly_fn(degree, poly))
		fprintf(stderr, "I can't solve that polynomial degree.\n");
	free_factor_list(&poly);
	free_factor_list(&result);
}
