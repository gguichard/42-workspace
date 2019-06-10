/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 05:08:55 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/10 20:11:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "fdf.h"

int			print_usage(t_fdf *fdf)
{
	if (fdf->opts.error)
		ft_dprintf(2, "fdf: illegal option -- %c\n", fdf->opts.error);
	ft_printf("USAGE: ./fdf [options] <map_file>\n\n");
	ft_printf("OPTIONS:\n");
	ft_printf("  -w <size>\tSpecify width for window size\n");
	ft_printf("  -h <size>\tSpecify height for window size\n");
	ft_printf("  -p <file>\tUse file as color palette\n");
	ft_printf("  -o\t\tLoad a wavefront obj file instead of a map\n");
	return (0);
}

static int	window_size(const char *str, int def_value)
{
	int	value;

	value = (str == NULL ? -1 : ft_atoi(str));
	if (value <= 0 || value > 2560)
	{
		ft_printf("fdf: warning: wrong winsize value (%d) replaced "
			"by default one (%d)\n"
			, value, def_value);
		return (def_value);
	}
	return (value);
}

void		update_winsize(t_fdf *fdf)
{
	if (!has_opt(&fdf->opts, 'w'))
		fdf->winsize.width = WIN_WIDTH;
	else
		fdf->winsize.width = window_size(get_optarg(&fdf->opts, 'w')
				, WIN_WIDTH);
	if (!has_opt(&fdf->opts, 'h'))
		fdf->winsize.height = WIN_HEIGHT;
	else
		fdf->winsize.height = window_size(get_optarg(&fdf->opts, 'h')
				, WIN_HEIGHT);
}

int			exit_fdf(t_fdf *fdf)
{
	clean_fdf(fdf);
	exit(0);
	return (0);
}
