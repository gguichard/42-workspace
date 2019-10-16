/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:03:18 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/16 13:57:19 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "computorv1.h"
#include "ast.h"
#include "utils.h"

void		reorder_poly_factors(factor_list_t **lst)
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

static int	get_poly_degree(factor_list_t *lst, int *has_neg_power)
{
	int				degree = 0;
	factor_list_t	*node;

	*has_neg_power = 0;
	for (node = lst; node != NULL; node = node->next)
	{
		if (degree < node->power)
			degree = node->power;
		if (node->power < 0)
			*has_neg_power = 1;
	}
	return degree;
}

static void	print_reduced_form(factor_list_t *poly)
{
	fprintf(stdout, "Reduced form: ");
	print_factor_list(poly);
	fprintf(stdout, " = 0\n");
}

void		solve_poly(ast_node_t *root)
{
	factor_list_t	*poly;
	factor_list_t	*result;
	int				degree;
	int				has_neg_power = 0;

	poly = ast_factor_list(root->left);
	result = ast_factor_list(root->right);
	reduce_factor_list(&poly, result);
	reorder_poly_factors(&poly);
	print_reduced_form(poly);
	degree = get_poly_degree(poly, &has_neg_power);
	fprintf(stdout, "Polynomial degree: %d\n", degree);
	if (has_neg_power)
		fprintf(stderr, "I can't solve equation with negative powers.\n");
	else if (!solve_poly_fn(degree, poly))
		fprintf(stderr, "I can't solve that polynomial degree.\n");
	free_factor_list(&poly);
	free_factor_list(&result);
}
