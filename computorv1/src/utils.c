/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:42:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/15 19:00:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "computorv1.h"

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

void		print_value(double value)
{
	if (value == (int)value)
		fprintf(stdout, "%d", (int)value);
	else
		fprintf(stdout, "%.2f", value);
}

void		print_factors(factor_list_t *lst)
{
	factor_list_t	*node;

	if (lst == NULL)
		fprintf(stdout, "0");
	for (node = lst; node != NULL; node = node->next)
	{
		if (node != lst || node->value < 0)
		{
			if (node != lst)
				fprintf(stdout, " ");
			fprintf(stdout, "%c", node->value < 0 ? '-' : '+');
			if (node->value >= 0 || node != lst)
				fprintf(stdout, " ");
		}
		if (node->value != 1.0 && node->value != -1.0)
		{
			print_value(node->value < 0 ? -(node->value) : node->value);
			fprintf(stdout, " * ");
		}
		fprintf(stdout, "X^%d", (int)node->power);
	}
}
