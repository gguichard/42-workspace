/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 22:17:07 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/26 22:18:07 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "ft_ssl.h"

size_t	align_up(size_t n, int mod)
{
	size_t	mod_res;

	mod_res = n % mod;
	if (mod_res == 0)
		return (n);
	else
		return ((n - mod_res) + mod);
}
