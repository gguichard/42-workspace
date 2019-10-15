/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factor_list_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:17:22 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/15 18:21:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "computorv1.h"

factor_list_t	*factor_list_plus(factor_list_t *a, factor_list_t *b)
{
	factor_list_t	*lst = NULL;
	factor_list_t	*node;

	for (node = a; node != NULL; node = node->next)
		get_factor_or_create(&lst, node->power)->value += node->value;
	for (node = b; node != NULL; node = node->next)
		get_factor_or_create(&lst, node->power)->value += node->value;
	return lst;
}

factor_list_t	*factor_list_minus(factor_list_t *a, factor_list_t *b)
{
	factor_list_t	*lst = NULL;
	factor_list_t	*node;

	for (node = a; node != NULL; node = node->next)
		get_factor_or_create(&lst, node->power)->value += node->value;
	for (node = b; node != NULL; node = node->next)
		get_factor_or_create(&lst, node->power)->value -= node->value;
	return lst;
}

factor_list_t	*factor_list_mul(factor_list_t *a, factor_list_t *b)
{
	factor_list_t	*lst = NULL;
	factor_list_t	*node_a, *node_b;
	int				power;
	double			result;

	for (node_a = a; node_a != NULL; node_a = node_a->next)
	{
		for (node_b = b; node_b != NULL; node_b = node_b->next)
		{
			power = node_a->power + node_b->power;
			result = node_a->value * node_b->value;
			get_factor_or_create(&lst, power)->value += result;
		}
	}
	return lst;
}

factor_list_t	*factor_list_div(factor_list_t *a, factor_list_t *b)
{
	factor_list_t	*lst = NULL;
	factor_list_t	*node_a, *node_b;
	int				power;
	double			result;

	for (node_a = a; node_a != NULL; node_a = node_a->next)
	{
		for (node_b = b; node_b != NULL; node_b = node_b->next)
		{
			power = node_a->power - node_b->power;
			result = node_a->value / node_b->value;
			get_factor_or_create(&lst, power)->value += result;
		}
	}
	return lst;
}

factor_list_t	*factor_list_pow(factor_list_t *a, factor_list_t *b)
{
	factor_list_t	*lst = NULL;
	factor_list_t	*node_a, *node_b;
	int				power;
	double			result;

	for (node_a = a; node_a != NULL; node_a = node_a->next)
	{
		for (node_b = b; node_b != NULL; node_b = node_b->next)
		{
			power = node_a->power * node_b->value;
			result = pow_fn(node_a->value, node_b->value);
			get_factor_or_create(&lst, power)->value += result;
		}
	}
	return lst;
}
