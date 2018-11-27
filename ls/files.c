/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:28:17 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/27 22:23:35 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

static t_flist	*load_link_data(t_flist *file)
{
	struct stat	link_data;

	if (!(file->link = ft_strnew(file->stat.st_size))
		|| readlink(file->path, file->link, file->stat.st_size) < 0)
		return (NULL);
	if (stat(file->link, &link_data) < 0)
		errno = 0;
	else if (S_ISDIR(link_data.st_mode))
		file->is_dir = 1;
	return (file);
}

static t_flist	*load_group_data(t_flist *file)
{
	struct passwd	*passwd;
	struct group	*group;

	if (!(passwd = getpwuid(file->stat.st_uid))
			|| !(group = getgrgid(file->stat.st_gid))
			|| !(file->pw_name = ft_strdup(passwd->pw_name))
			|| !(file->gr_name = ft_strdup(group->gr_name)))
		return (NULL);
	return (file);
}

t_flist			*load_file(t_opt *opt, const char *path, const char *name)
{
	t_flist			*file;

	if (!(file = flist_create_elem())
			|| !(file->path = get_path(path, name)))
		return (flist_free_elem(file));
	if (name != NULL && !(file->name = ft_strdup(name)))
		return (flist_free_elem(file));
	if (lstat(file->path, &(file->stat)) < 0)
	{
		file_error(path);
		return (flist_free_elem(file));
	}
	file->is_dir = S_ISDIR(file->stat.st_mode);
	if (S_ISLNK(file->stat.st_mode) && !(load_link_data(file)))
		return (flist_free_elem(file));
	if (opt->options & LST_OPT && !(load_group_data(file)))
		return (flist_free_elem(file));
	return (file);
}
