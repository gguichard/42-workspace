/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 09:00:24 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/23 20:39:21 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/ioctl.h>
# include <sys/stat.h>

# define VALID_OPTIONS "alrtR"
# define COLUMN_OPT	((long)1 << 63)

typedef struct	s_opt
{
	char			**files;
	long			options;
	struct winsize	ws;
}				t_opt;

typedef struct	s_flist
{
	struct dirent	*data;
	struct stat		*stat;
	struct s_flist	*next;
}				t_flist;

typedef struct	s_out
{
	int			cols;
	int			rows;
	int			size;
	int			f_count;
	int			f_width;
}				t_out;

long			opt_mask(char c);

void			malloc_error(void);

void			parse_options(t_opt *opt, int argc, char **argv);

void			flist_add(t_flist **lst, struct dirent *data, struct stat *stat
					, int (*cmp)(t_flist *f1, t_flist *f2));

int				sort_by_name(t_flist *f1, t_flist *f2);

void			show_columns(t_opt *opt, t_flist *lst);

#endif
