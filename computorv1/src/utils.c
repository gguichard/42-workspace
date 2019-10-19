/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:42:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/18 16:25:30 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "computorv1.h"

void		exit_unexpected(void)
{
	fprintf(stderr, "Unexpected error\n");
	exit(0);
}

void		fprintf_char_n_times(FILE *stream, char c, size_t times)
{
	size_t	n;

	for (n = 0; n < times; n++)
		fprintf(stream, "%c", c);
}

static void	print_real_value(double value)
{
	// TODO: print value as irreductible fraction
	if (abs_fn(value - (int)value) < EPSILON)
		fprintf(stdout, "%d", (int)value);
	else
		fprintf(stdout, "%.4f", value);
}

void		print_complex(int nb, complex_t value)
{
	fprintf(stdout, "X%d = ", nb);
	print_real_value(value.real);
	if (value.imag != 0.0)
	{
		fprintf(stdout, " %c i * ", value.imag < 0.0 ? '-' : '+');
		print_real_value(abs_fn(value.imag));
	}
	fprintf(stdout, "\n");
}

void		print_factor_list(factor_list_t *lst)
{
	factor_list_t	*node;

	if (lst == NULL)
		fprintf(stdout, "0");
	for (node = lst; node != NULL; node = node->next)
	{
		if (node != lst || node->value < 0)
		{
			fprintf(stdout, "%s%c%s"
				, node != lst ? " " : ""
				, node->value < 0 ? '-' : '+'
				, (node->value >= 0 || node != lst) ? " " : "");
		}
		if ((int)node->power == 0)
			print_real_value(abs_fn(node->value));
		else
		{
			if (abs_fn(node->value) != 1.0)
				print_real_value(abs_fn(node->value));
			fprintf(stdout, "X");
			if ((int)node->power != 1)
				fprintf(stdout, "^%d", (int)node->power);
		}
	}
}
