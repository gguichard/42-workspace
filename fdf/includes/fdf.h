/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:36:42 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/06 16:39:36 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_WIDTH 800
# define WIN_HEIGHT 800

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
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_data;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_mlx;

typedef struct	s_fdf
{
	int			width;
	int			height;
	t_type		type;
	t_mlx		lib;
}				t_fdf;

#endif
