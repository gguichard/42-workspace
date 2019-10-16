/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 20:24:14 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/16 19:34:42 by gguichar         ###   ########.fr       */
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
	double	c = get_factor_value_or_default(poly, 0, 0.0);

	if (c != 0.0)
		fprintf(stderr, "I can't solve that equation because it is wrong.\n");
	else
		fprintf(stdout, "The solutions are all real numbers.\n");
}

static void		solve_linear_poly(factor_list_t *poly)
{
	double	a = get_factor_value_or_default(poly, 1, 0.0);
	double	b = get_factor_value_or_default(poly, 0, 0.0);

	fprintf(stdout, "X = %f\n", -b / a);
}

static void		print_complex(int nb, complex_t value)
{
	if (value.imag == 0.0)
		fprintf(stdout, "X%d = %f\n", nb, value.real);
	else
		fprintf(stdout, "X%d = %f %c %fi\n"
			, nb, value.real, value.imag < 0.0 ? '-' : '+', abs_fn(value.imag));
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

static double	compute_poly(factor_list_t *poly, double x)
{
	factor_list_t	*node;
	double			value = 0.0;

	for (node = poly; node != NULL; node = node->next)
		value += (node->value * pow_fn(x, node->power));
	return value;
}

static double	search_real_root(factor_list_t *poly, factor_list_t *derivative)
{
	int		iter;
	double	x0 = 1.0, x1 = 1.0;
	double	y_prime;

	// Search a root thanks to Newton-Raphson
	for (iter = 0; iter < 100; iter++)
	{
		y_prime = compute_poly(derivative, x0);
		if (abs_fn(y_prime) < 1e-14)
			break;
		x1 = x0 - (compute_poly(poly, x0) / y_prime);
		if (abs_fn(x1 - x0) <= 1e-6)
			break;
		x0 = x1;
	}
	return x1;
}

static void		solve_cubic_poly(factor_list_t *poly)
{
	factor_list_t	*derivative;
	complex_t		x0, x1, x2;
	double			a, b, c;

	derivative = factor_list_derivate(poly);
	reorder_poly_factors(&derivative);
	fprintf(stdout, "Derivative function: ");
	print_factor_list(derivative);
	fprintf(stdout, "\n");
	x0 = new_complex(search_real_root(poly, derivative), 0.0);
	if (abs_fn(x0.real) <= 1e-6)
	{
		fprintf(stdout, "The triple real solution is:\n");
		print_complex(0, x0);
	}
	else
	{
		c = get_factor_value_or_default(poly, 0, 0.0) / -(x0.real);
		b = (get_factor_value_or_default(poly, 1, 0.0) - c) / -(x0.real);
		a = (get_factor_value_or_default(poly, 2, 0.0) - b) / -(x0.real);
		solve_quadratic(a, b, c, &x1, &x2);
		fprintf(stdout, "The three solutions are:\n");
		print_complex(0, x0);
		print_complex(1, x1);
		print_complex(2, x2);
	}
}
