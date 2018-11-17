/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:08:56 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/13 22:46:45 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fillit.h"

void	ft_exiterror(void)
{
	ft_putstr("error");
	ft_putchar('\n');
	exit(1);
}

int		count_active_bits(unsigned char byte)
{
	int	count;

	count = 0;
	while (byte)
	{
		if (byte & 1)
			count++;
		byte >>= 1;
	}
	return (count);
}
