/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:56:27 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/26 19:54:50 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

t_flist	*flist_create_elem(void)
{
	t_flist	*file;

	if (!(file = (t_flist *)malloc(sizeof(*file))))
		return (NULL);
	file->path = NULL;
	file->name = NULL;
	file->pw_name = NULL;
	file->gr_name = NULL;
	file->date = NULL;
	file->link = NULL;
	file->next = NULL;
	return (file);
}

t_flist	*flist_free_elem(t_flist *file)
{
	if (file != NULL)
	{
		free(file->path);
		free(file->name);
		free(file->pw_name);
		free(file->gr_name);
		free(file->date);
		free(file->link);
		free(file);
	}
	return (NULL);
}

t_flist	*flist_clean(t_flist *lst)
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

void	flist_add(t_flist **lst, t_flist *file)
{
	file->next = *lst;
	*lst = file;
}

void	flist_push_back(t_flist **lst, t_flist *file)
{
	t_flist	*current;

	current = *lst;
	if (current == NULL)
		*lst = file;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = file;
	}
}
