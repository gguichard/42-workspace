/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bad_atof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 13:42:59 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/16 14:07:45 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

double	ft_bad_atof(const char *str)
{
	char	*dotptr;
	char	*endptr;
	long	int_part;
	long	float_part;
	double	f;

	f = 0;
	int_part = ft_strtol(str, &endptr, 0);
	if (*endptr != '.')
		float_part = 0;
	else
	{
		dotptr = endptr;
		float_part = ft_strtol(dotptr + 1, &endptr, 10);
		f += float_part / (double)ft_pow(10, (int)(endptr - dotptr - 1));
	}
	f += int_part;
	return (f);
}
