/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 05:08:55 by gguichar          #+#    #+#             */
/*   Updated: 2019/01/01 16:05:28 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "fdf.h"

int			print_usage(t_fdf *fdf)
{
	if (fdf->opt->error)
		ft_dprintf(2, "fdf: illegal option -- %c\n", fdf->opt->error);
	ft_printf("USAGE: ./fdf [options] <map_file>\n\n");
	ft_printf("OPTIONS:\n");
	ft_printf("  -w <size>\tSpecify width for window size\n");
	ft_printf("  -h <size>\tSpecify height for window size\n");
	ft_printf("  -p <file>\tUse file as color palette\n");
	return (0);
}

static int	window_size(const char *str)
{
	int	size;

	if (str == NULL)
		return (-1);
	size = ft_atoi(str);
	if (size <= 0 || size > 2560)
		return (-1);
	return (size);
}

int			check_options(t_fdf *fdf)
{
	if ((fdf->width = has_opt(fdf->opt, 'w')
				? window_size(get_optarg(fdf->opt, 'w')) : WIN_WIDTH) < 0)
	{
		ft_dprintf(2, "fdf: please provide valid width or remove -w option\n");
		return (0);
	}
	if ((fdf->height = has_opt(fdf->opt, 'h')
				? window_size(get_optarg(fdf->opt, 'h')) : WIN_HEIGHT) < 0)
	{
		ft_dprintf(2, "fdf: please provide valid height or remove -h option\n");
		return (0);
	}
	if (has_opt(fdf->opt, 'p')
			&& !parse_palette(get_optarg(fdf->opt, 'p'), fdf))
	{
		ft_dprintf(2, "fdf: unable to load color palette\n");
		return (0);
	}
	return (1);
}

int			exit_fdf(t_fdf *fdf)
{
	clean_fdf(fdf);
	exit(0);
	return (0);
}
