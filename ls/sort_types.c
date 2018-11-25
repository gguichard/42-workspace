/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:16:12 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/25 16:16:51 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

int	sort_asc_name(t_flist *f1, t_flist *f2)
{
	return (ft_strcmp(f1->path, f2->path));
}

int	sort_desc_time(t_flist *f1, t_flist *f2)
{
	int	res;

	res = (f2->stat.st_mtimespec.tv_sec - f1->stat.st_mtimespec.tv_sec);
	if (res == 0)
		res = (f2->stat.st_mtimespec.tv_nsec - f1->stat.st_mtimespec.tv_nsec);
	if (res == 0)
		return (ft_strcmp(f1->path, f2->path));
	return (res);
}
