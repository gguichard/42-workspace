/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:06:30 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/28 13:55:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_ls.h"

static void	define_functions(t_opt *opt)
{
	if (opt->options & SRT_T_OPT)
		opt->cmp = &sort_mtime;
	else if (opt->options & SRT_S_OPT)
		opt->cmp = &sort_size;
	else
		opt->cmp = &sort_name;
	opt->cmp_mul = (opt->options & REV_OPT) ? -1 : 1;
	opt->print = &show_simple;
	if (!(opt->options & ONE_OPT))
	{
		if (opt->options & LST_OPT)
			opt->print = &show_list;
		else if (opt->options & COL_OPT || isatty(STDOUT_FILENO))
		{
			if (ioctl(0, TIOCGWINSZ, &(opt->win_size)) < 0)
			{
				opt->print = &show_simple;
				return ;
			}
			opt->print = &show_columns;
		}
	}
}

static int	add_files(t_opt *opt, t_flist **def, int count, char **files)
{
	t_flist	*file;
	int		i;

	i = 0;
	while (i < count)
	{
		if ((file = load_file(opt, files[i], NULL)) != NULL)
		{
			file->name = ft_strdup(files[i]);
			if (!file->is_dir)
				flist_add(def, file);
			else
			{
				flist_add(&(opt->files), file);
				(opt->count)++;
			}
		}
		i++;
	}
	return (1);
}

static void	load_files(t_opt *opt, int count, char **args)
{
	t_flist	*file;
	t_flist	*def;

	if (count == 0)
	{
		if ((file = load_file(opt, ".", NULL)) != NULL)
		{
			flist_add(&(opt->files), file);
			(opt->count)++;
		}
	}
	else
	{
		def = NULL;
		add_files(opt, &def, count, args);
		opt->files = flist_sort(opt->files, opt->cmp, opt->cmp_mul);
		if (def != NULL)
		{
			def = flist_sort(def, opt->cmp, opt->cmp_mul);
			opt->show_total = 0;
			opt->print(opt, def);
			flist_clean(def);
			(opt->loops)++;
		}
	}
}

int			main(int argc, char **argv)
{
	t_opt	opt;
	t_flist	*tmp;

	opt.files = NULL;
	opt.count = 0;
	opt.loops = 0;
	parse_options(&opt, argc, argv);
	define_functions(&opt);
	load_files(&opt, argc - opt.offset, &(argv[opt.offset]));
	opt.show_total = 1;
	while (opt.files != NULL)
	{
		ls(&opt, opt.files);
		tmp = opt.files->next;
		flist_free_elem(opt.files);
		opt.files = tmp;
		(opt.loops)++;
	}
	return (0);
}
