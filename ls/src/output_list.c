/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 09:27:09 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/28 10:28:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/xattr.h>
#include <sys/types.h>
#include <sys/acl.h>
#include "libft.h"
#include "ft_ls.h"

static void	additional_data(t_flist *file, time_t now)
{
	long long	diff;
	char		*tmp;

	file->x_attr = listxattr(file->path, NULL, 0, XATTR_NOFOLLOW) > 0
		? '@' : ' ';
	diff = now - file->stat.st_mtime;
	if (diff < 0)
		diff = -diff;
	tmp = ctime(&(file->stat.st_mtime));
	if (diff <= 15811200)
		file->date = ft_strndup(tmp + 4, 12);
	else
	{
		if (file->stat.st_mtime >= 253402297200)
			ft_asprintf(&(file->date), "%.7s %.5s", tmp + 4, tmp + 24);
		else
			ft_asprintf(&(file->date), "%.7s%.5s", tmp + 4, tmp + 19);
	}
}

static void	init_out(t_out *out)
{
	out->total_blocks = 0;
	out->w_links = 0;
	out->w_user = 0;
	out->w_group = 0;
	out->w_size = 0;
	out->w_major = 0;
	out->w_minor = 0;
	out->w_date = 0;
}

static void	prepare_padding(t_out *out, t_flist *lst)
{
	time_t	now;

	now = time(NULL);
	while (lst != NULL)
	{
		additional_data(lst, now);
		out->total_blocks += lst->stat.st_blocks;
		out->w_links = ft_max(ft_llsize(lst->stat.st_nlink), out->w_links);
		if (lst->pw_name != NULL)
			out->w_user = ft_max(ft_strlen(lst->pw_name), out->w_user);
		if (lst->gr_name != NULL)
			out->w_group = ft_max(ft_strlen(lst->gr_name), out->w_group);
		if (!S_ISBLK(lst->stat.st_mode) && !S_ISCHR(lst->stat.st_mode))
			out->w_size = ft_max(ft_llsize(lst->stat.st_size), out->w_size);
		else
		{
			out->w_major = ft_max(ft_llsize(major(lst->stat.st_rdev))
					, out->w_major);
			out->w_minor = ft_max(ft_llsize(minor(lst->stat.st_rdev))
					, out->w_minor);
			out->w_size = ft_max(out->w_major + out->w_minor + 3, out->w_size);
		}
		out->w_date = ft_max(ft_strlen(lst->date), out->w_date);
		lst = lst->next;
	}
}

static void	show_device(t_out *out, t_flist *file)
{
	ft_printf("%c%s%s%s%c %*d %-*s  %-*s   %*ld, %*ld %s %s%s%s\n"
			, file_type(file->stat.st_mode)
			, file_permissions(file->stat.st_mode, 6)
			, file_permissions(file->stat.st_mode, 3)
			, file_permissions(file->stat.st_mode, 0)
			, file->x_attr
			, out->w_links, file->stat.st_nlink
			, out->w_user, file->pw_name, out->w_group, file->gr_name
			, out->w_major, (unsigned long)major(file->stat.st_rdev)
			, out->w_minor, (unsigned long)minor(file->stat.st_rdev)
			, file->date, file->name
			, file->link != NULL ? " -> " : ""
			, file->link != NULL ? file->link : "");
}

void		show_list(t_opt *opt, t_flist *lst)
{
	t_out	out;

	init_out(&out);
	prepare_padding(&out, lst);
	if (opt->show_total)
		ft_printf("total %d\n", out.total_blocks);
	while (lst != NULL)
	{
		if (S_ISBLK(lst->stat.st_mode) || S_ISCHR(lst->stat.st_mode))
			show_device(&out, lst);
		else
			ft_printf("%c%s%s%s%c %*d %-*s  %-*s  %*d %s %s%s%s\n"
					, file_type(lst->stat.st_mode)
					, file_permissions(lst->stat.st_mode, 6)
					, file_permissions(lst->stat.st_mode, 3)
					, file_permissions(lst->stat.st_mode, 0)
					, lst->x_attr
					, out.w_links, lst->stat.st_nlink
					, out.w_user, lst->pw_name, out.w_group, lst->gr_name
					, out.w_size, lst->stat.st_size
					, lst->date, lst->name
					, lst->link != NULL ? " -> " : ""
					, lst->link != NULL ? lst->link : "");
		lst = lst->next;
	}
}
