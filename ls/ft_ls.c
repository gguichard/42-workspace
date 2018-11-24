/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 08:59:15 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/24 16:38:40 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

static t_flist	*ls_path(t_opt *opt, char *path
		, int (*cmp)(t_flist *, t_flist *))
{
	DIR				*dir;
	t_flist			*lst;
	struct dirent	*data;
	char			*f_path;

	if (!(dir = opendir(path)))
	{
		file_error(path);
		return (NULL);
	}
	lst = NULL;
	while ((data = readdir(dir)) != NULL)
	{
		if ((data->d_name)[0] == '.' && !(opt->options & HID_OPT))
			continue ;
		f_path = get_path(path, data->d_name);
		flist_add(&lst, data->d_name, f_path, cmp);
	}
	closedir(dir);
	return (lst);
}

static void		ls(t_opt *opt, char *path, void (*f)(t_opt *, t_flist *)
		, int (*cmp)(t_flist *, t_flist *))
{
	t_flist	*lst;

	lst = ls_path(opt, path, cmp);
	if (lst != NULL)
		f(opt, lst);
	if (opt->options & REC_OPT)
	{
		while (lst != NULL)
		{
			if (S_ISDIR(lst->stat->st_mode) && (lst->name)[0] != '.')
			{
				ft_printf("\n%s:\n", lst->path);
				ls(opt, lst->path, f, cmp);
			}
			lst = lst->next;
		}
	}
}

int				main(int argc, char **argv)
{
	t_opt	opt;
	int		index;
	void	(*f)(t_opt *, t_flist *);
	int		(*cmp)(t_flist *, t_flist *);

	parse_options(&opt, argc, argv);
	if (opt.options & COL_OPT
		|| (isatty(STDOUT_FILENO) && !(opt.options & LST_OPT)))
		f = &show_columns;
	else
		f = &show_simple;
	if (opt.options & SRT_OPT)
		cmp = (opt.options & REV_OPT) ? &sort_by_time_asc : &sort_by_time_desc;
	else
		cmp = (opt.options & REV_OPT) ? &sort_by_name_desc : &sort_by_name_asc;
	index = 0;
	while ((opt.files)[index] != NULL)
	{
		if (opt.f_count > 1 && !(opt.options & REC_OPT))
			ft_printf("%s:\n", (opt.files)[index]);
		ls(&opt, (opt.files)[index], f, cmp);
		if (opt.f_count > 1 && !(opt.options & REC_OPT)
				&& (opt.files)[index + 1] != NULL)
			ft_printf("\n");
		index++;
	}
	return (0);
}
