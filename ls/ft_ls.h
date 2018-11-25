/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 09:00:24 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/25 22:55:37 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <time.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>

# define VALID_OPTIONS "alrtCR1"

# define HID_OPT 0x1
# define SRT_OPT ((long)1 << 19)
# define LST_OPT ((long)1 << 11)
# define COL_OPT ((long)1 << 28)
# define REC_OPT ((long)1 << 43)
# define REV_OPT ((long)1 << 17)
# define ONE_OPT ((long)1 << 53)

typedef struct		s_flist
{
	char			*name;
	char			*path;
	struct stat		stat;
	char			*pw_name;
	char			*gr_name;
	struct s_flist	*next;
}					t_flist;

typedef struct		s_opt
{
	long			options;
	int				(*cmp)(t_flist *, t_flist *);
	int				loops;
	struct s_flist	*files;
	struct winsize	ws;
}					t_opt;

typedef struct		s_out
{
	int				cols;
	int				rows;
	int				size;
	int				w_file;
	int				w_links;
	int				w_user;
	int				w_group;
	int				w_size;
}					t_out;

long			opt_mask(char c);
void			file_error(const char *file);
char			*get_path(const char *dir, const char *file);

char			f_type(mode_t st_mode);
char			f_perm(mode_t mode, int perm);

int				parse_options(t_opt *opt, int argc, char **argv);

int				sort_asc_name(t_flist *f1, t_flist *f2);
int				sort_desc_time(t_flist *f1, t_flist *f2);

t_flist			*flist_create_elem(void);
t_flist			*flist_free_elem(t_flist *elem);
t_flist			*flist_clean(t_flist *lst);
int				flist_stat(t_flist *file);
t_flist			*flist_diradd(t_flist **lst, const char *path
		, int (*cmp)(t_flist *, t_flist *));
t_flist			*flist_add(t_flist **lst, const char *name, const char *path);
t_flist			*flist_sort(t_flist *lst, int (*cmp)(t_flist *, t_flist *));
void			flist_push_back(t_flist **lst, t_flist *elem);
void			flist_sort_insert(t_flist **lst, t_flist *elem
		, int (*cmp)(t_flist *, t_flist *));

void			show_columns(t_opt *opt, t_flist *lst);
void			show_simple(t_opt *opt, t_flist *lst);

#endif
