/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 20:24:14 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/15 21:05:43 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "computorv1.h"

static void	solve_const_poly(factor_list_t *lst);
static void	solve_linear_poly(factor_list_t *lst);
static void	solve_quad_poly(factor_list_t *lst);

static const solve_map_t	solve_fn[] = {
	{0, solve_const_poly},
	{1, solve_linear_poly},
	{2, solve_quad_poly}
};

int			solve_poly_fn(int degree, factor_list_t *poly)
{
	size_t	idx;

	for (idx = 0; idx < (sizeof(solve_fn) / sizeof(solve_fn[0])); idx++)
	{
		if (solve_fn[idx].degree == degree)
		{
			solve_fn[idx].fn(poly);
			return 1;
		}
	}
	return 0;
}

static void	solve_const_poly(factor_list_t *lst)
{
	double	c = get_factor_value_or_default(lst, 0, 0.0);

	if (c != 0.0)
		fprintf(stderr, "Equation is wrong. There is no solution.\n");
	else
		fprintf(stdout, "The solutions are all real numbers.\n");
}

static void	solve_linear_poly(factor_list_t *lst)
{
	double	a = get_factor_value_or_default(lst, 1, 0.0);
	double	b = get_factor_value_or_default(lst, 0, 0.0);

	fprintf(stdout, "X = %f\n", -b / a);
}

static void	solve_quad_poly(factor_list_t *lst)
{
	double	a = get_factor_value_or_default(lst, 2, 0.0);
	double	b = get_factor_value_or_default(lst, 1, 0.0);
	double	c = get_factor_value_or_default(lst, 0, 0.0);
	double	delta = (b * b) - (4 * a * c), sqrt_delta;

	// TODO: recreate sqrt function
	if (delta < 0.0)
	{
		sqrt_delta = sqrt(-delta);
		fprintf(stdout, "Discriminant is strictly negative, "
			"the two complex solutions are:\n");
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
				"the two real solutions are:\n");
		else
			fprintf(stdout, "Discriminant is zero, the real solution is:\n");
		fprintf(stdout, "X1 = %f\n", (-b - sqrt_delta) / (2 * a));
		if (delta > 0.0)
			fprintf(stdout, "X2 = %f\n", (-b + sqrt_delta) / (2 * a));
	}
}
