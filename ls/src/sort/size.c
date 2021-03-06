/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 10:40:45 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/19 15:25:40 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	sort_size(t_flist *f1, t_flist *f2)
{
	if (f2->stat.st_size > f1->stat.st_size)
		return (1);
	if (f2->stat.st_size < f1->stat.st_size)
		return (-1);
	return (0);
}
