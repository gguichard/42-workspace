/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:03:18 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/15 18:57:41 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "computorv1.h"
#include "ast.h"

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
			continue;
		}
		prev = node;
	}
}

static void	solve_linear(factor_list_t *lst)
{
	double	a = get_factor_value_or_default(lst, 1, 0.0);
	double	b = get_factor_value_or_default(lst, 0, 0.0);

	fprintf(stdout, "X = %f\n", -b / a);
}

static void	solve_quadratic(factor_list_t *lst)
{
	double	a = get_factor_value_or_default(lst, 2, 0.0);
	double	b = get_factor_value_or_default(lst, 1, 0.0);
	double	c = get_factor_value_or_default(lst, 0, 0.0);
	double	delta = (b * b) - (4 * a * c), sqrt_delta;

	if (delta < 0.0)
	{
		sqrt_delta = sqrt(-delta);
		fprintf(stdout, "Discriminant is strictly negative, "
			"the two solutions are:\n");
		fprintf(stdout, "X1 = %.2f+%.2fi\n"
			, -b / (2 * a), sqrt_delta / (2 * a));
		fprintf(stdout, "X2 = %.2f-%.2fi\n"
			, -b / (2 * a), sqrt_delta / (2 * a));
	}
	else
	{
		sqrt_delta = sqrt(delta);
		if (delta > 0.0)
			fprintf(stdout, "Discriminant is strictly positive, "
				"the two solutions are:\n");
		else
			fprintf(stdout, "Discriminant is zero, the two solutions are:\n");
		fprintf(stdout, "X1 = %f\n", (-b - sqrt_delta) / (2 * a));
		fprintf(stdout, "X2 = %f\n", (-b + sqrt_delta) / (2 * a));
	}
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
	switch (degree)
	{
		case 0:
			if (get_factor_value_or_default(poly, 0, 0.0) != 0.0)
				fprintf(stderr, "Equation is wrong. There is no solution.\n");
			else
				fprintf(stderr, "The solutions are all real numbers.\n");
			break;
		case 1:
			solve_linear(poly);
			break;
		case 2:
			solve_quadratic(poly);
			break;
		default:
			fprintf(stderr, "I can't solve that polynomial degree.\n");
			break;
	}
	free_factor_list(&poly);
	free_factor_list(&result);
}
