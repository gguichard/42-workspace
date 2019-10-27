/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 20:08:06 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/27 17:10:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "malloc.h"

size_t	align_up(size_t n, int mod)
{
	size_t	mod_res;

	mod_res = n % mod;
	if (mod_res == 0)
		return (n);
	else
		return ((n - mod_res) + mod);
}

int		order_from_size(size_t size, size_t min_size)
{
	size_t	order;

	if (size < min_size)
		size = min_size;
	order = 0;
	if ((size & (size - 1)) != 0)
		order += 1;
	while ((size >>= 1) != 0)
		order += 1;
	return (order);
}
