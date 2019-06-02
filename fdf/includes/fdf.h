/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:36:42 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/02 14:14:01 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "options.h"
# include "winsize.h"
# include "vectors.h"

typedef struct		s_color
{
	int				max;
	unsigned int	value;
}					t_color;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	unsigned int	*img_data;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_mlx;

typedef struct		s_pos
{
	int				x;
	int				y;
	int				z;
	t_vec2d			proj;
	int				color;
}					t_pos;

typedef struct		s_fdf
{
	t_mlx			lib;
	t_opts			opts;
	int				argc;
	char			**argv;
	t_winsize		winsize;
	int				rows;
	int				cols;
	t_list			*palette;
	t_pos			*pos;
	int				*z_buffer;
	int				keys;
	double			matrix[4][4];
	int				drag;
	t_vec2d			prev_cursor;
}					t_fdf;

int					clean_fdf(t_fdf *fdf);

/*
** UTILS.
*/
int					print_usage(t_fdf *fdf);
int					check_options(t_fdf *fdf);
int					exit_fdf(t_fdf *fdf);

/*
** MATHS UTILS.
*/
int					lint(int start, int end, double percent);
double				pcnt(int start, int end, int current);
unsigned int		get_color(unsigned int start, unsigned int end
	, double percent);

/*
** COLORS parsing.
*/
int					parse_palette(const char *file, t_fdf *fdf);
int					get_palette_color(t_fdf *fdf, int z);

/*
** PARSING.
*/
int					read_file(const char *name, t_fdf *fdf);

/*
** GRAPHICS.
*/
void				fill_window_image(t_fdf *fdf);

/*
** HOOKS.
*/
int					loop_hook(t_fdf *fdf);
int					keypress_hook(int keycode, t_fdf *fdf);
int					keyrelease_hook(int keycode, t_fdf *fdf);
int					expose_hook(t_fdf *fdf);
int					button_hook(int button, int x, int y, t_fdf *fdf);
int					motion_hook(int x, int y, t_fdf *fdf);

int					handle_move(t_fdf *fdf);
int					handle_scale(t_fdf *fdf);
int					handle_depth(t_fdf *fdf);
int					handle_rotation(t_fdf *fdf, char axis);
void				rotate_with_mat(t_fdf *fdf, int delta, char axis);

#endif
