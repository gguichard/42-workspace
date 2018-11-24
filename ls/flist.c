/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:56:27 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/24 11:40:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

static void	insert_elem(t_flist **lst, t_flist *elem
		, int (*cmp)(t_flist *f1, t_flist *f2))
{
	t_flist	*previous;
	t_flist	*current;

	previous = NULL;
	current = *lst;
	while (current != NULL)
	{
		if (cmp(elem, current) <= 0)
		{
			elem->next = current;
			break ;
		}
		previous = current;
		current = current->next;
	}
	if (previous == NULL)
		*lst = elem;
	else
		previous->next = elem;
}

t_flist		*flist_add(t_flist **lst, char *name, char *path
		, int (*cmp)(t_flist *f1, t_flist *f2))
{
	t_flist		*file;

	if (!(file = (t_flist *)malloc(sizeof(*file))))
		return (NULL);
	file->name = ft_strdup(name);
	file->path = path;
	if (lstat(path, &(file->stat)) < 0)
		return (NULL);
	file->is_dir = file->stat.st_mode & S_IFDIR;
	file->mlast = file->stat.st_mtimespec;
	file->next = NULL;
	insert_elem(lst, file, cmp);
	return (file);
}
