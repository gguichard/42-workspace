/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:56:27 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/25 21:49:17 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

static t_flist	*flist_create_elem(void)
{
	t_flist	*file;

	if (!(file = (t_flist *)malloc(sizeof(*file))))
		return (NULL);
	file->name = NULL;
	file->path = NULL;
	file->next = NULL;
	return (file);
}

t_flist			*flist_free_elem(t_flist *file)
{
	if (file != NULL)
	{
		free(file->name);
		free(file->path);
		free(file);
	}
	return (NULL);
}

t_flist			*flist_clean(t_flist *lst)
{
	t_flist	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		flist_free_elem(lst);
		lst = tmp;
	}
	return (NULL);
}

t_flist			*flist_dircopy(t_flist *file)
{
	t_flist	*folder;

	if (!(folder = flist_create_elem()))
		return (NULL);
	if (!(folder->name = ft_strdup(file->name))
			|| !(folder->path = ft_strdup(file->path)))
		return (flist_free_elem(folder));
	ft_memcpy(&(folder->stat), &(file->stat), sizeof(struct stat));
	return (folder);
}

t_flist			*flist_add(t_flist **lst, const char *name, const char *path)
{
	t_flist	*file;

	if (!(file = flist_create_elem()))
		return (NULL);
	if (name != NULL && !(file->name = ft_strdup(name)))
		return (flist_free_elem(file));
	if (!(file->path = get_path(path, name))
			|| lstat(file->path, &(file->stat)) < 0)
		return (flist_free_elem(file));
	file->pw_name = "WIP";
	file->gr_name = "WIP";
	file->next = *lst;
	*lst = file;
	return (file);
}
