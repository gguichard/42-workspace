/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 08:59:15 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/27 19:39:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "libft.h"
#include "ft_ls.h"

static t_flist	*ls_dir(t_opt *opt, t_flist *folder)
{
	DIR				*dir;
	t_flist			*lst;
	struct dirent	*data;
	t_flist			*file;

	if (!(dir = opendir(folder->path)))
		return (file_error(folder->name));
	lst = NULL;
	while ((data = readdir(dir)) != NULL)
	{
		if ((data->d_name)[0] == '.' && !(opt->options & HID_OPT))
			continue ;
		if (!(file = load_file(opt, folder->path, data->d_name)))
			return (flist_clean(lst));
		flist_add(&lst, file);
		if (opt->options & REC_OPT && S_ISDIR(file->stat.st_mode)
				&& !ft_strequ(file->name, ".") && !ft_strequ(file->name, ".."))
		{
			if (!(file = load_file(opt, folder->path, data->d_name)))
				return (flist_clean(lst));
			flist_sort_insert(&(folder->next), file, opt->cmp);
		}
	}
	closedir(dir);
	return (lst);
}

void			ls(t_opt *opt, t_flist *folder)
{
	t_flist	*lst;
	t_flist	*next;

	next = folder->next;
	folder->next = NULL;
	errno = 0;
	lst = ls_dir(opt, folder);
	flist_push_back(&(folder->next), next);
	if (errno != ENOENT)
	{
		if (opt->loops > 0)
			ft_printf("\n%s:\n", folder->path);
		else if (opt->count > 1)
			ft_printf("%s:\n", folder->path);
	}
	if (lst != NULL)
	{
		lst = flist_sort(lst, opt->cmp);
		opt->print(opt, lst);
		flist_clean(lst);
	}
}
