/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 09:00:24 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/24 12:06:54 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <time.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <sys/stat.h>

# define VALID_OPTIONS "alrtR"

# define HID_OPT 0x1
# define SRT_OPT ((long)1 << 19)
# define LST_OPT ((long)1 << 11)
# define COL_OPT ((long)1 << 63)
# define REC_OPT ((long)1 << 43)
# define REV_OPT ((long)1 << 17)

typedef struct	s_opt
{
	int				f_count;
	char			**files;
	long			options;
	struct winsize	ws;
}				t_opt;

typedef struct	s_flist
{
	char			*name;
	char			*path;
	int				is_dir;
	struct stat		stat;
	struct timespec	mlast;
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

char			f_type(mode_t st_mode);
char			f_perm(mode_t mode, int perm);

void			parse_options(t_opt *opt, int argc, char **argv);

int				sort_by_name_asc(t_flist *f1, t_flist *f2);
int				sort_by_name_desc(t_flist *f1, t_flist *f2);
int				sort_by_time_asc(t_flist *f1, t_flist *f2);
int				sort_by_time_desc(t_flist *f1, t_flist *f2);

t_flist			*flist_add(t_flist **lst, char *name, char *path
		, int (*cmp)(t_flist *f1, t_flist *f2));

void			show_columns(t_opt *opt, t_flist *lst);
void			show_simple(t_opt *opt, t_flist *lst);

#endif
