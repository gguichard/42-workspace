/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:16:12 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/24 14:15:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

int	sort_by_name_asc(t_flist *f1, t_flist *f2)
{
	return (ft_strcmp(f1->name, f2->name));
}

int	sort_by_name_desc(t_flist *f1, t_flist *f2)
{
	return (-ft_strcmp(f1->name, f2->name));
}

int	sort_by_time_asc(t_flist *f1, t_flist *f2)
{
	int	res;

	res = (f1->stat->st_mtimespec.tv_sec - f2->stat->st_mtimespec.tv_sec);
	if (res == 0)
		res = (f1->stat->st_mtimespec.tv_nsec - f2->stat->st_mtimespec.tv_nsec);
	if (res == 0)
		return (sort_by_name_desc(f1, f2));
	return (res);
}

int	sort_by_time_desc(t_flist *f1, t_flist *f2)
{
	int	res;

	res = (f2->stat->st_mtimespec.tv_sec - f1->stat->st_mtimespec.tv_sec);
	if (res == 0)
		res = (f2->stat->st_mtimespec.tv_nsec - f1->stat->st_mtimespec.tv_nsec);
	if (res == 0)
		return (sort_by_name_asc(f1, f2));
	return (res);
}
