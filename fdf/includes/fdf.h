/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:36:42 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/30 01:40:57 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_WIDTH 400
# define WIN_HEIGHT 400

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
	t_proj			proj;
	t_mlx			lib;
	t_pos			**pos;
	int				rows;
	int				cols;
}					t_fdf;

/*
** PARSING.
*/
int					read_file(const char *name, t_fdf *fdf);

/*
** GRAPHICS.
*/
void				iso(t_pos *pos, int *x, int *y);
void				draw_map(t_fdf *fdf);

#endif
