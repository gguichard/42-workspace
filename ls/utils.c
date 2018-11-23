/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:25:24 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/23 10:48:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

long	opt_mask(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1 << (c - 'a'));
	else if (c >= 'A' && c <= 'Z')
		return ((long)1 << (c - 'A') << 26);
	return (0);
}

void	malloc_error(void)
{
	ft_dprintf(2, "ft_ls: malloc error\n");
	exit(1);
}
