/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factor_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:59:20 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/16 13:52:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "computorv1.h"

factor_list_t	*get_factor(factor_list_t *lst, int power)
{
	factor_list_t	*node;

	for (node = lst; node != NULL; node = node->next)
	{
		if (node->power == power)
			return node;
	}
	return NULL;
}

double			get_factor_value_or_default(factor_list_t *lst
	, int power, double def)
{
	factor_list_t	*node;

	node = get_factor(lst, power);
	if (node != NULL)
		return node->value;
	return def;
}

factor_list_t	*get_factor_or_create(factor_list_t **lst, int power)
{
	factor_list_t	*node;

	node = get_factor(*lst, power);
	if (node == NULL)
	{
		node = malloc(sizeof(factor_list_t));
		node->next = *lst;
		node->value = 0;
		node->power = power;
		*lst = node;
	}
	return node;
}

factor_list_t	*factor_list_derivate(factor_list_t *poly)
{
	factor_list_t	*lst = NULL;
	factor_list_t	*node;

	for (node = poly; node != NULL; node = node->next)
	{
		if (node->power > 0)
			get_factor_or_create(&lst, node->power - 1)->value = node->value * node->power;
	}
	return lst;
}

void			reduce_factor_list(factor_list_t **lst, factor_list_t *from)
{
	factor_list_t	*node;
	factor_list_t	*next, *prev = NULL;

	for (node = from; node != NULL; node = node->next)
		get_factor_or_create(lst, node->power)->value -= node->value;

	// Suppression des facteurs nuls
	for (node = *lst; node != NULL; node = next)
	{
		next = node->next;
		if (node->value != 0.0)
			prev = node;
		else
		{
			free(node);
			if (prev == NULL)
				*lst = next;
			else
				prev->next = next;
		}
	}
}

void			free_factor_list(factor_list_t **lst)
{
	factor_list_t	*node;
	factor_list_t	*next;

	for (node = *lst; node != NULL; node = next)
	{
		next = node->next;
		free(node);
	}
	*lst = NULL;
}
