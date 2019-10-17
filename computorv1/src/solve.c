/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 20:24:14 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/17 17:28:45 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "computorv1.h"
#include "utils.h"

static void		solve_const_poly(factor_list_t *poly);
static void		solve_linear_poly(factor_list_t *poly);
static void		solve_quad_poly(factor_list_t *poly);
static void		solve_cubic_poly(factor_list_t *poly);

static const solve_map_t	solve_fn[] = {
	{0, solve_const_poly},
	{1, solve_linear_poly},
	{2, solve_quad_poly},
	{3, solve_cubic_poly}
};

int				solve_poly_fn(int degree, factor_list_t *poly)
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

static void		solve_const_poly(factor_list_t *poly)
{
	double	k;

	k = get_factor_value_or_default(poly, 0, 0.0);
	if (k != 0.0)
		fprintf(stderr, "There is no solution.\n");
	else
		fprintf(stdout, "Every complex number is a solution.\n");
}

static void		solve_linear_poly(factor_list_t *poly)
{
	double	a, b;

	a = get_factor_value_or_default(poly, 1, 0.0);
	b = get_factor_value_or_default(poly, 0, 0.0);
	print_complex(0, new_complex(-b / a, 0));
}

static double	solve_quadratic(double quad_a, double quad_b, double quad_c
	, complex_t *x0, complex_t *x1)
{
	double	delta, delta_sqrt;

	delta = (quad_b * quad_b) - (4 * quad_a * quad_c);
	if (delta < 0.0)
	{
		delta_sqrt = sqrt_fn(-delta);
		*x0 = new_complex(-quad_b / (2 * quad_a), -delta_sqrt / (2 * quad_a));
		*x1 = new_complex(-quad_b / (2 * quad_a), delta_sqrt / (2 * quad_a));
	}
	else
	{
		delta_sqrt = sqrt_fn(delta);
		*x0 = new_complex((-quad_b - delta_sqrt) / (2 * quad_a), 0.0);
		*x1 = new_complex((-quad_b + delta_sqrt) / (2 * quad_a), 0.0);
	}
	return delta;
}

static void		solve_quad_poly(factor_list_t *poly)
{
	double		a, b, c;
	double		delta;
	complex_t	x0, x1;

	a = get_factor_value_or_default(poly, 2, 0.0);
	b = get_factor_value_or_default(poly, 1, 0.0);
	c = get_factor_value_or_default(poly, 0, 0.0);
	delta = solve_quadratic(a, b, c, &x0, &x1);
	if (delta == 0.0)
		fprintf(stdout, "Discriminant is zero, the real solution is:\n");
	else if (delta < 0.0)
		fprintf(stdout, "Discriminant is strictly negative, "
			"the two complex solutions are:\n");
	else
		fprintf(stdout, "Discriminant is strictly positive, "
			"the two real solutions are:\n");
	print_complex(0, x0);
	if (delta != 0.0)
		print_complex(1, x1);
}

static void		solve_cubic_poly(factor_list_t *poly)
{
	factor_list_t	*derivative;
	int				succeed;
	complex_t		x0, x1, x2;
	double			a, b, c;

	derivative = factor_list_derivate(poly);
	reorder_poly_factors(&derivative);
	fprintf(stdout, "Derivative function: ");
	print_factor_list(derivative);
	fprintf(stdout, "\n");
	x0 = new_complex(search_real_root(poly, derivative, &succeed), 0.0);
	if (!succeed)
		fprintf(stderr, "Sorry, I'm unable to find a root.\n");
	else
	{
		// Round the number and ignore the non significant decimal part due to
		// Newton-Raphson precision errors.
		if (x0.real * (1 / EPSILON) < 10.0)
			x0.real = (int)x0.real;
		x1 = x2 = x0;
		a = get_factor_value_or_default(poly, 3, 0.0);
		b = get_factor_value_or_default(poly, 2, 0.0) + a * x0.real;
		c = get_factor_value_or_default(poly, 1, 0.0) + b * x0.real;
		if (abs_fn(a) > EPSILON)
			solve_quadratic(a, b, c, &x1, &x2);
		fprintf(stdout, "The three solutions are:\n");
		print_complex(0, x0);
		print_complex(1, x1);
		print_complex(2, x2);
	}
	free_factor_list(&derivative);
}
