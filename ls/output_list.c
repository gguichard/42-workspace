/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 09:27:09 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/27 14:17:54 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "libft.h"
#include "ft_ls.h"

static char	*format_date(t_flist *file, time_t now)
{
	long long	diff;
	char		*tmp;
	char		*date;

	diff = now - file->stat.st_mtime;
	if (diff < 0)
		diff = -diff;
	tmp = ctime(&(file->stat.st_mtime));
	if (diff <= 15811200)
		return (ft_strndup(tmp + 4, 12));
	ft_asprintf(&date, "%.7s%.5s", tmp + 4, tmp + 19);
	return (date);
}

static void	prepare_list(t_out *out, t_flist *lst)
{
	time_t	now;

	now = time(NULL);
	out->total_blocks = 0;
	out->w_links = 0;
	out->w_user = 0;
	out->w_group = 0;
	out->w_size = 0;
	out->w_date = 0;
	while (lst != NULL)
	{
		out->total_blocks += lst->stat.st_blocks;
		lst->date = format_date(lst, now);
		out->w_links = ft_max(ft_llsize(lst->stat.st_nlink), out->w_links);
		if (lst->pw_name != NULL)
			out->w_user = ft_max(ft_strlen(lst->pw_name), out->w_user);
		if (lst->gr_name != NULL)
			out->w_group = ft_max(ft_strlen(lst->gr_name), out->w_group);
		out->w_size = ft_max(ft_llsize(lst->stat.st_size), out->w_size);
		out->w_date = ft_max(ft_strlen(lst->date), out->w_date);
		lst = lst->next;
	}
}

static void	show_list_details(t_opt *opt, t_flist *lst)
{
	t_out	out;
	mode_t	mode;

	prepare_list(&out, lst);
	if (opt->show_total)
		ft_printf("total %d\n", out.total_blocks);
	while (lst != NULL)
	{
		mode = lst->stat.st_mode;
		ft_printf("%c%s%s%s%c %*d %-*s  %-*s  %*d %s %s%s%s\n"
				, file_type(mode)
				, file_permissions(mode, 6)
				, file_permissions(mode, 3)
				, file_permissions(mode, 0)
				, ' '
				, out.w_links, lst->stat.st_nlink
				, out.w_user, lst->pw_name
				, out.w_group, lst->gr_name
				, out.w_size, lst->stat.st_size
				, lst->date
				, lst->name
				, lst->link != NULL ? " -> " : ""
				, lst->link != NULL ? lst->link : "");
		lst = lst->next;
	}
}

void		show_list(t_opt *opt, t_flist *lst)
{
	if (opt->options & LST_OPT)
		show_list_details(opt, lst);
	else
	{
		while (lst != NULL)
		{
			ft_printf("%s\n", lst->name);
			lst = lst->next;
		}
	}
}
