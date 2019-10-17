/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:38:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/17 13:12:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define EPSILON 1e-6

# include "computorv1.h"

typedef struct
{
	double	real;
	double	imag;
} complex_t;

complex_t	new_complex(double real, double imag);

double		abs_fn(double nb);
double		pow_fn(double nb, int pow);
double		sqrt_fn(double nb);
int			euclidean_gcd(int a, int b);
double		search_real_root(factor_list_t *poly, factor_list_t *derivative
	, int *succeed);

void		exit_unexpected(void);

void		print_complex(int nb, complex_t value);
void		print_factor_list(factor_list_t *lst);

#endif
