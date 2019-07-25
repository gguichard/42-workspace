/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 20:08:06 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/23 23:08:45 by gguichar         ###   ########.fr       */
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
