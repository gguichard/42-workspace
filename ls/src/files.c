/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:28:17 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/19 15:24:16 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "libft.h"
#include "ft_ls.h"

static t_flist	*load_link_data(t_flist *file)
{
	size_t		size;
	struct stat	link_data;

	size = file->stat.st_size;
	if (size == 0)
		size = PATH_MAX;
	if (!(file->link = ft_strnew(size))
		|| readlink(file->path, file->link, size) < 0)
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

	if ((passwd = getpwuid(file->stat.st_uid)) != NULL)
		file->pw_name = ft_strdup(passwd->pw_name);
	if ((group = getgrgid(file->stat.st_gid)) != NULL)
		file->gr_name = ft_strdup(group->gr_name);
	if (file->pw_name == NULL)
		file->pw_name = ft_lltoa(file->stat.st_uid);
	if (file->gr_name == NULL)
		file->gr_name = ft_lltoa(file->stat.st_gid);
	if (file->pw_name == NULL || file->gr_name == NULL)
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
