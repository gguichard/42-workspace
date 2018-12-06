/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:36:42 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/06 20:09:49 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_WIDTH 400
# define WIN_HEIGHT 400

typedef enum	e_type
{
	ISO
}				t_type;

typedef struct	s_image
{
	void		*ptr;
	char		*data;
}				t_image;

typedef struct	s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	unsigned int	*img_data;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}				t_mlx;

typedef struct	s_fdf
{
	int			width;
	int			height;
	t_type		type;
	t_mlx		lib;
}				t_fdf;

typedef struct	s_pos
{
	int			x;
	int			y;
	int			z;
}				t_pos;

int				read_file(const char *name);

#endif
