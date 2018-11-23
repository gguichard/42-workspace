/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:56:27 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/23 16:39:58 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

void	flist_add(t_flist **lst, struct dirent *data, struct stat *stat 
	, int (*cmp)(t_flist *f1, t_flist *f2))
{
	t_flist	*file;
	t_flist	*current;
	t_flist	*previous;

	if (!(file = (t_flist *)malloc(sizeof(*file))))
		malloc_error();
	file->data = data;
	file->stat = stat;
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
}
