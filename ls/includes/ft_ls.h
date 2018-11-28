/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 09:00:24 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/28 09:50:27 by gguichar         ###   ########.fr       */
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
	char			*path;
	char			*name;
	struct stat		stat;
	int				is_dir;
	char			*pw_name;
	char			*gr_name;
	char			*date;
	char			*link;
	char			x_attr;
	struct s_flist	*next;
}					t_flist;

typedef struct		s_opt
{
	int				offset;
	long			options;
	int				(*cmp)(t_flist *, t_flist *);
	void			(*print)(struct s_opt *, t_flist *);
	struct s_flist	*files;
	int				count;
	int				loops;
	struct winsize	win_size;
	int				show_total;
}					t_opt;

typedef struct		s_out
{
	int				cols;
	int				rows;
	int				size;
	int				total_blocks;
	int				w_file;
	int				w_links;
	int				w_user;
	int				w_group;
	int				w_size;
	int				w_major;
	int				w_minor;
	int				w_date;
}					t_out;

void				parse_options(t_opt *opt, int argc, char **argv);

t_flist				*load_file(t_opt *opt, const char *path, const char *name);
void				ls(t_opt *opt, t_flist *folder);

long				opt_mask(char c);
void				*file_error(const char *file);
void				*str_error(const char *err);
char				*get_path(const char *dir, const char *file);

char				file_type(mode_t st_mode);
char				*file_permissions(mode_t mode, int shift);

int					sort_asc_name(t_flist *f1, t_flist *f2);
int					sort_desc_name(t_flist *f1, t_flist *f2);
int					sort_asc_time(t_flist *f1, t_flist *f2);
int					sort_desc_time(t_flist *f1, t_flist *f2);

t_flist				*flist_create_elem(void);
t_flist				*flist_free_elem(t_flist *elem);
t_flist				*flist_clean(t_flist *lst);
t_flist				*flist_sort(t_flist *lst, int (*cmp)(t_flist *, t_flist *));
void				flist_add(t_flist **lst, t_flist *file);
void				flist_push_back(t_flist **lst, t_flist *file);
void				flist_sort_insert(t_flist **lst, t_flist *file
		, int (*cmp)(t_flist *, t_flist *));

void				show_simple(t_opt *opt, t_flist *lst);
void				show_columns(t_opt *opt, t_flist *lst);
void				show_list(t_opt *opt, t_flist *lst);

#endif
