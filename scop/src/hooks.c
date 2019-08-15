/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 04:05:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/08/15 15:20:49 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "scop.h"

int	expose_hook(t_scop *scop)
{
	(void)scop;
	return (0);
}

int	loop_hook(t_scop *scop)
{
	(void)scop;
	return (0);
}

int	exit_window(t_scop *scop)
{
	(void)scop;
	exit(0);
	return (0);
}
