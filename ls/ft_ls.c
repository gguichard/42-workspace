/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 08:59:15 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/27 16:42:09 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

static t_flist	*load_file(t_opt *opt, const char *path, const char *name)
{
	t_flist			*file;
	struct passwd	*passwd;
	struct group	*group;
	struct stat		link_data;

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
	if (S_ISLNK(file->stat.st_mode))
	{
		if (!(file->link = ft_strnew(file->stat.st_size)))
			return (flist_free_elem(file));
		if (readlink(file->path, file->link, file->stat.st_size) < 0)
			return (flist_free_elem(file));
		if (stat(file->link, &link_data) != -1 && S_ISDIR(link_data.st_mode))
			file->is_dir = 1;
	}
	if (opt->options & LST_OPT)
	{
		if (!(passwd = getpwuid(file->stat.st_uid))
				|| !(group = getgrgid(file->stat.st_gid))
				|| !(file->pw_name = ft_strdup(passwd->pw_name))
				|| !(file->gr_name = ft_strdup(group->gr_name)))
			return (flist_free_elem(file));
	}
	return (file);
}

static t_flist	*ls_path(t_opt *opt, t_flist *folder)
{
	DIR				*dir;
	t_flist			*lst;
	t_flist			*next;
	struct dirent	*data;
	t_flist			*file;

	if (!(dir = opendir(folder->path)))
	{
		file_error(folder->name);
		return (NULL);
	}
	lst = NULL;
	next = folder->next;
	folder->next = NULL;
	while ((data = readdir(dir)) != NULL)
	{
		if ((data->d_name)[0] == '.' && !(opt->options & HID_OPT))
			continue ;
		if (!(file = load_file(opt, folder->path, data->d_name)))
			return (flist_clean(lst));
		flist_add(&lst, file);
		if (opt->options & REC_OPT && S_ISDIR(file->stat.st_mode)
				&& !ft_strequ(file->name, ".")
				&& !ft_strequ(file->name, ".."))
			flist_sort_insert(&(folder->next)
					, load_file(opt, folder->path, data->d_name)
					, opt->cmp);
	}
	closedir(dir);
	flist_push_back(&(folder->next), next);
	return (lst);
}

static void		ls(t_opt *opt, t_flist *folder, void (*f)(t_opt *, t_flist *))
{
	t_flist	*lst;

	errno = 0;
	lst = ls_path(opt, folder);
	if (errno != ENOENT && opt->loops > 0)
		ft_printf("\n%s:\n", folder->path);
	else if (errno != ENOENT && opt->total > 1)
		ft_printf("%s:\n", folder->path);
	if (lst != NULL)
	{
		lst = flist_sort(lst, opt->cmp);
		f(opt, lst);
		flist_clean(lst);
	}
}

int				main(int argc, char **argv)
{
	t_opt	opt;
	int		offset;
	void	(*f)(t_opt *, t_flist *);
	t_flist	*tmp;
	t_flist	*files;

	offset = parse_options(&opt, argc, argv);
	if (opt.options & SRT_OPT)
		opt.cmp = (opt.options & REV_OPT) ? &sort_asc_time : &sort_desc_time;
	else
		opt.cmp = (opt.options & REV_OPT) ? &sort_desc_name : &sort_asc_name;
	if (opt.options & LST_OPT
			|| opt.options & ONE_OPT
			|| (!isatty(STDOUT_FILENO) && !(opt.options & COL_OPT)))
		f = &show_list;
	else
	{
		if (ioctl(0, TIOCGWINSZ, &(opt.ws)) < 0)
			exit_error("unable to get term size");
		f = &show_columns;
	}
	opt.total = 0;
	opt.files = NULL;
	opt.loops = 0;
	opt.show_total = 1;
	if (offset >= argc)
	{
		if ((tmp = load_file(&opt, ".", NULL)) != NULL)
		{
			flist_add(&(opt.files), tmp);
			(opt.total)++;
		}
	}
	else
	{
		files = NULL;
		while (offset < argc)
		{
			if ((tmp = load_file(&opt, argv[offset], NULL)) != NULL)
			{
				tmp->name = ft_strdup(argv[offset]);
				if (!tmp->is_dir)
					flist_add(&files, tmp);
				else
				{
					flist_add(&(opt.files), tmp);
					(opt.total)++;
				}
			}
			offset++;
		}
		opt.files = flist_sort(opt.files, opt.cmp);
		if (files != NULL)
		{
			files = flist_sort(files, opt.cmp);
			opt.show_total = 0;
			f(&opt, files);
			opt.show_total = 1;
			flist_clean(files);
			(opt.loops)++;
		}
	}
	while (opt.files != NULL)
	{
		ls(&opt, opt.files, f);
		tmp = opt.files->next;
		flist_free_elem(opt.files);
		opt.files = tmp;
		(opt.loops)++;
	}
	return (0);
}
