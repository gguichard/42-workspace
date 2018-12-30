/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:36:42 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/30 05:36:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_WIDTH 1280
# define WIN_HEIGHT 800

typedef enum		e_proj
{
	ISO
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

typedef struct		s_pos
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_pos;

typedef struct		s_fdf
{
	int				width;
	int				height;
	int				scale;
	int				depth;
	t_proj			proj;
	t_mlx			lib;
	t_pos			**pos;
	int				rows;
	int				cols;
}					t_fdf;

int					clean_mlx(t_fdf *fdf);
int					exit_fdf(t_fdf *fdf);

/*
** PARSING.
*/
int					read_file(const char *name, t_fdf *fdf);

/*
** GRAPHICS.
*/
void				iso(t_fdf *fdf, t_pos *pos, t_pos *to);
void				fill_window_image(t_fdf *fdf);

void				draw_pixel(t_fdf *fdf, int x, int y);
void				draw_line(t_fdf *fdf, t_pos pos1, t_pos pos2);

/*
** HOOKS.
*/
int					key_hook(int keycode, t_fdf *fdf);
int					expose_hook(t_fdf *fdf);

#endif
