/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:56:27 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/23 22:11:19 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

t_flist	*flist_add(t_flist **lst, const char *f_name
	, int (*cmp)(t_flist *f1, t_flist *f2))
{
	t_flist	*file;
	t_flist	*current;
	t_flist	*previous;

	if (!(file = (t_flist *)malloc(sizeof(*file))))
		malloc_error();
	file->name = ft_strdup(f_name);
	file->next = NULL;
	previous = NULL;
	current = *lst;
	while (current != NULL)
	{
		if (cmp(file, current) <= 0)
		{
			file->next = current;
			break ;
		}
		previous = current;
		current = current->next;
	}
	if (previous == NULL)
		*lst = file;
	else
		previous->next = file;
	return (file);
}
