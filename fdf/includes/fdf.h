/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:36:42 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/30 07:43:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "options.h"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 800

typedef enum		e_proj
{
	ISO, PARALLEL
}					t_proj;

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

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_point;

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct		s_fdf
{
	t_opt			*opt;
	int				width;
	int				height;
	int				scale;
	int				depth;
	t_proj			proj;
	void			(*f_proj)(struct s_fdf *, t_point *, t_pos *);
	t_mlx			lib;
	t_point			**point;
	int				rows;
	int				cols;
	int				offset_x;
	int				offset_y;
}					t_fdf;

int					point_to_index(t_fdf *fdf, t_point *point);
int					clean_mlx(t_fdf *fdf);
int					exit_fdf(t_fdf *fdf);

/*
** PARSING.
*/
int					read_file(const char *name, t_fdf *fdf);

/*
** GRAPHICS.
*/
void				iso(t_fdf *fdf, t_point *point, t_pos *to);
void				parallel(t_fdf *fdf, t_point *point, t_pos *to);

void				fill_window_image(t_fdf *fdf);

void				draw_pixel(t_fdf *fdf, int x, int y);
void				draw_line(t_fdf *fdf, t_pos pos1, t_pos pos2);

/*
** HOOKS.
*/
int					key_hook(int keycode, t_fdf *fdf);
int					expose_hook(t_fdf *fdf);

#endif
