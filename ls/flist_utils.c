/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flist_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 22:42:27 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/25 22:44:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

t_flist	*flist_create_elem(void)
{
	t_flist	*file;

	if (!(file = (t_flist *)malloc(sizeof(*file))))
		return (NULL);
	file->name = NULL;
	file->path = NULL;
	file->next = NULL;
	return (file);
}

t_flist	*flist_free_elem(t_flist *file)
{
	if (file != NULL)
	{
		free(file->name);
		free(file->path);
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
