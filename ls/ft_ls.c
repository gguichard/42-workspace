/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 08:59:15 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/23 22:33:57 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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
	t_flist	*lst;

	lst = ls_path(opt, path);
	if (lst != NULL)
	{
		if (opt->options & COLUMN_OPT && isatty(1))
			show_columns(opt, lst);
		else
			show_simple(opt, lst);
	}
	if (opt->options & opt_mask('R'))
	{
		while (lst != NULL)
		{
			if (lst->is_dir && (lst->name)[0] != '.')
			{
				ft_printf("\n%s:\n", lst->path);
				ls(opt, lst->path);
			}
			lst = lst->next;
		}
	}
}

int				main(int argc, char **argv)
{
	t_opt	opt;
	int		index;

	opt.options = 0;
	parse_options(&opt, argc, argv);
	if (opt.files == NULL)
		ls(&opt, ".");
	else
	{
		index = 0;
		while ((opt.files)[index] != NULL)
		{
			if (!(opt.options & opt_mask('R')))
				ft_printf("%s:\n", (opt.files)[index]);
			ls(&opt, (opt.files)[index]);
			if (!(opt.options & opt_mask('R')) && (opt.files)[index + 1] != NULL)
				ft_printf("\n");
			index++;
		}
	}
	return (0);
}
