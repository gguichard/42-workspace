/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:42:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/16 16:00:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "utils.h"
#include "computorv1.h"

void	print_value(double value)
{
	if (value == (int)value)
		fprintf(stdout, "%d", (int)value);
	else
		fprintf(stdout, "%.2f", value);
}

void	print_factor_list(factor_list_t *lst)
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
		if (node->value != 1.0 && node->value != -1.0)
		{
			print_value(node->value < 0 ? -(node->value) : node->value);
			fprintf(stdout, " * ");
		}
		fprintf(stdout, "X^%d", (int)node->power);
	}
}
