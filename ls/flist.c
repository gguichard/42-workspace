/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:56:27 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/24 16:32:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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
	t_flist			*file;
	struct stat		stat;
	struct passwd	*passwd;
	struct group	*group;
	ssize_t			ret;

	if (!(file = (t_flist *)malloc(sizeof(*file))))
		return (NULL);
	file->name = ft_strdup(name);
	file->path = path;
	if (lstat(path, &stat) < 0
		|| !(file->stat = (struct stat *)malloc(sizeof(struct stat))))
		return (NULL);
	ft_memcpy(file->stat, &stat, sizeof(stat));
	file->link = NULL;
	if (S_ISLNK(stat.st_mode))
	{
		if (!(file->link = (char *)malloc((stat.st_size + 1) * sizeof(char))))
			return (NULL);
		if ((ret = readlink(path, file->link, stat.st_size)) < 0)
			return (NULL);
		(file->link)[ret] = '\0';
	}
	if (!(passwd = getpwuid(file->stat->st_uid))
		|| !(group = getgrgid(file->stat->st_gid)))
		return (NULL);
	file->pw_name = ft_strdup(passwd->pw_name);
	file->gr_name = ft_strdup(group->gr_name);
	file->next = NULL;
	insert_elem(lst, file, cmp);
	return (file);
}
