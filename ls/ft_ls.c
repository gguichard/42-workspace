/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 08:59:15 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/23 22:15:52 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

static t_flist	*ls_path(t_opt *opt, char *path)
{
	DIR				*dir;
	t_flist			*lst;
	struct dirent	*data;
	struct stat		stat;
	char			*f_path;
	t_flist			*file;

	dir = opendir(path);
	if (dir == NULL)
	{
		file_error(path);
		return (NULL);
	}
	lst = NULL;
	while ((data = readdir(dir)) != NULL)
	{
		if ((data->d_name)[0] != '.' || opt->options & opt_mask('a'))
		{
			f_path = get_path(path, data->d_name);
			if (lstat(f_path, &stat) < 0)
			{
				file_error(f_path);
				continue ;
			}
			file = flist_add(&lst, data->d_name, &sort_by_name);
			file->path = f_path;
			file->is_dir = stat.st_mode & S_IFDIR;
		}
	}
	closedir(dir);
	return (lst);
}

static void		ls(t_opt *opt, char *path)
{
	t_flist	*files;

	files = ls_path(opt, path);
	if (files != NULL && opt->options & COLUMN_OPT)
		show_columns(opt, files);
	if (opt->options & opt_mask('R'))
	{
		while (files != NULL)
		{
			if (files->is_dir && (files->name)[0] != '.')
			{
				ft_printf("\n%s:\n", files->path);
				ls(opt, files->path);
			}
			files = files->next;
		}
	}
}

int				main(int argc, char **argv)
{
	t_opt	opt;

	opt.options = 0;
	parse_options(&opt, argc, argv);
	if (opt.files != NULL)
		ls(&opt, opt.files[0]);
	else
		ls(&opt, ".");
	return (0);
}
