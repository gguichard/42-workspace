/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 12:37:34 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/21 10:02:28 by gguichar         ###   ########.fr       */
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
	ft_printf("usage: checker [-%s] numbers ...\n", VALID_OPT);
	ft_printf("\tf [path] - read instructions from file\n");
	ft_printf("\tv - verbose mode\n");
	ft_printf("\th - show this help\n");
	return (0);
}
