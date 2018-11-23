/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 09:00:24 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/23 22:25:44 by gguichar         ###   ########.fr       */
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
	char			*name;
	char			*path;
	int				is_dir;
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
void			file_error(const char *file);
void			malloc_error(void);
char			*get_path(const char *dir, const char *file);

void			parse_options(t_opt *opt, int argc, char **argv);

t_flist			*flist_add(t_flist **lst, const char *f_name
					, int (*cmp)(t_flist *f1, t_flist *f2));

int				sort_by_name(t_flist *f1, t_flist *f2);

void			show_columns(t_opt *opt, t_flist *lst);
void			show_simple(t_opt *opt, t_flist *lst);

#endif
