/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 08:59:15 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/25 23:08:41 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

static t_flist	*ls_path(t_opt *opt, t_flist *folder)
{
	DIR				*dir;
	t_flist			*lst;
	t_flist			*next;
	struct dirent	*data;
	t_flist			*file;
	t_flist			*tmp;

	if (!(dir = opendir(folder->path)))
	{
		file_error((folder->name == NULL) ? "" : folder->name);
		return (NULL);
	}
	lst = NULL;
	next = folder->next;
	folder->next = NULL;
	while ((data = readdir(dir)) != NULL)
	{
		if ((data->d_name)[0] == '.' && !(opt->options & HID_OPT))
			continue ;
		if (!(file = flist_add(&lst, data->d_name, folder->path)))
			return (flist_clean(lst));
		if (opt->options & REC_OPT && S_ISDIR(file->stat.st_mode)
				&& !ft_strequ(file->name, ".")
				&& !ft_strequ(file->name, ".."))
		{
			if (!(tmp = flist_add(&(folder->next), file->path)))
				return (flist_clean(lst));
		}
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

	offset = parse_options(&opt, argc, argv);
	if (opt.options & SRT_OPT)
		opt.cmp = &sort_desc_time;
	else
		opt.cmp = &sort_asc_name;
	if (opt.options & LST_OPT
			|| opt.options & ONE_OPT
			|| (!isatty(STDOUT_FILENO) && !(opt.options & COL_OPT)))
		f = &show_simple;
	else
	{
		if (ioctl(0, TIOCGWINSZ, &(opt.ws)) < 0)
		{
			ft_dprintf(2, "ft_ls: unable to get term size\n");
			return (1);
		}
		f = &show_columns;
	}
	opt.files = NULL;
	if (offset >= argc)
		flist_diradd(&(opt.files), ".", opt.cmp);
	while (offset < argc)
	{
		flist_diradd(&(opt.files), argv[offset], opt.cmp);
		offset++;
	}
	opt.loops = 0;
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
