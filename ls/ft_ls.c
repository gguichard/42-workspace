/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 08:59:15 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/23 16:40:58 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "ft_ls.h"

t_flist	*ls_path(t_opt *opt, const char *path)
{
	DIR				*dir;
	struct dirent	*data;
	char			*file_path;
	struct stat		stat;
	t_flist			*lst;

	dir = opendir(path);
	if (dir == NULL)
	{
		ft_dprintf(2, "ft_ls: %s: %s\n", path, strerror(errno));
		exit(1);
	}
	lst = NULL;
	while ((data = readdir(dir)) != NULL)
	{
		if ((data->d_name)[0] != '.' || opt->options & opt_mask('a'))
		{
			ft_asprintf(&file_path, "%s/%s", path, data->d_name);
			if (lstat(file_path, &stat) < 0)
			{
				ft_dprintf(2, "ft_ls: %s: %s\n", file_path, strerror(errno));
				exit(1);
			}
			flist_add(&lst, data, &stat, &sort_by_name);
		}
	}
	closedir(dir);
	return (lst);
}

int		main(int argc, char **argv)
{
	t_opt	opt;
	t_flist	*files;

	opt.options = 0;
	parse_options(&opt, argc, argv);
	if (opt.files != NULL)
		files = ls_path(&opt, opt.files[0]);
	else
		files = ls_path(&opt, "./");
	if (opt.options & COLUMN_OPT)
		show_columns(&opt, files);
	return (0);
}
