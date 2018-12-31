/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 05:08:55 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/31 01:08:00 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "fdf.h"

int		window_size(const char *str)
{
	int	size;

	if (str == NULL)
		return (-1);
	size = ft_atoi(str);
	if (size <= 0 || size > 2560)
		return (-1);
	return (size);
}

int		exit_fdf(t_fdf *fdf)
{
	clean_mlx(fdf);
	exit(0);
	return (0);
}
