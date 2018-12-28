/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 12:37:34 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/28 16:34:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	show_error(void)
{
	ft_dprintf(2, "Error\n");
	return (0);
}

int	show_help(t_opt *opt)
{
	if (opt->error != 0)
		ft_dprintf(2, "checker: illegal option -- %c\n", opt->error);
	ft_printf("USAGE: checker [options] <numbers>\n\n");
	ft_printf("OPTIONS:\n");
	ft_printf("  -f <path>\tRead instructions from file\n");
	ft_printf("  -h\t\tShow this help\n");
	return (0);
}
