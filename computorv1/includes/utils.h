/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:38:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/16 19:34:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

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

void		print_value(double value);
void		print_factor_list(factor_list_t *lst);

#endif
