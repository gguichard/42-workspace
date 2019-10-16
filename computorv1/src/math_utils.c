/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:38:18 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/16 19:33:51 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

complex_t	new_complex(double real, double imag)
{
	complex_t	ret;

	ret.real = real;
	ret.imag = imag;
	return ret;
}

double		abs_fn(double nb)
{
	return nb < 0 ? -nb : nb;
}

double		pow_fn(double nb, int pow)
{
	double	result = 1;
	double	factor = (pow < 0 ? (1 / nb) : nb);

	while (pow != 0)
	{
		result *= factor;
		if (pow < 0)
			pow += 1;
		else
			pow -= 1;
	}
	return result;
}

double		sqrt_fn(double nb)
{
	double	x0 = 1.0, x1;
	int		iter;

	for (iter = 0; iter < 20; iter++)
	{
		x1 = 0.5 * (x0 + nb / x0);
		if (abs_fn(x1 - x0) <= 1e-6)
			break;
		x0 = x1;
	}
	return x1;
}
