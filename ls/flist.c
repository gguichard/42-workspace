/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:56:27 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/25 23:01:39 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

int		flist_stat(t_flist *file)
{
	return (lstat(file->path, &(file->stat)));
}

t_flist	*flist_diradd(t_flist **lst, const char *path
		, int (*cmp)(t_flist *, t_flist *))
{
	t_flist	*folder;

	if (!(folder = flist_create_elem())
			|| !(folder->name = ft_strdup(path))
			|| !(folder->path = ft_strdup(path)))
		return (flist_free_elem(folder));
	flist_stat(folder);
	flist_sort_insert(lst, folder, cmp);
	return (folder);
}

t_flist	*flist_add(t_flist **lst, const char *name, const char *path)
{
	t_flist	*file;

	if (!(file = flist_create_elem()))
		return (NULL);
	if (!(file->name = ft_strdup(name))
			|| !(file->path = get_path(path, name)))
		return (flist_free_elem(file));
	flist_stat(file);
	file->pw_name = "WIP";
	file->gr_name = "WIP";
	file->next = *lst;
	*lst = file;
	return (file);
}
