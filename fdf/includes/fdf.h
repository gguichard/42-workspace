/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:36:42 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/31 03:37:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "options.h"

# define WIN_WIDTH 1640
# define WIN_HEIGHT 1280

typedef enum		e_proj
{
	ISO, PARALLEL
}					t_proj;

typedef struct		s_color
{
	int				max;
	int				value;
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
	int				proj_x;
	int				proj_y;
	int				color;
}					t_pos;

typedef struct		s_move
{
	int				x;
	int				y;
	int				scale;
	int				depth;
	int				angle;
}					t_move;

typedef struct		s_cam
{
	int				x;
	int				y;
}					t_cam;

typedef struct		s_fdf
{
	t_opt			*opt;
	int				argc;
	char			**argv;
	int				width;
	int				height;
	t_list			*palette;
	t_cam			cam;
	int				scale;
	int				depth;
	int				angle;
	double			angle_rad;
	t_proj			proj;
	void			(*f_proj)(struct s_fdf *, t_pos *);
	t_mlx			lib;
	t_pos			**pos;
	int				rows;
	int				cols;
	int				offset_x;
	int				offset_y;
	t_move			move;
}					t_fdf;

int					check_options(t_fdf *fdf);
int					clean_mlx(t_fdf *fdf);
int					exit_fdf(t_fdf *fdf);

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
void				iso(t_fdf *fdf, t_pos *pos);
void				parallel(t_fdf *fdf, t_pos *pos);

void				fill_window_image(t_fdf *fdf);

void				draw_pixel(t_fdf *fdf, t_pos start, t_pos end, t_pos curr);
void				draw_line(t_fdf *fdf, t_pos start, t_pos end);

/*
** HOOKS.
*/
int					loop_hook(t_fdf *fdf);
int					keypress_hook(int keycode, t_fdf *fdf);
int					keyrelease_hook(int keycode, t_fdf *fdf);
int					expose_hook(t_fdf *fdf);

int					handle_move(t_fdf *fdf);
int					handle_scale(t_fdf *fdf);
int					handle_depth(t_fdf *fdf);
int					handle_angle(t_fdf *fdf);
int					handle_proj(t_fdf *fdf, int keycode);

#endif
