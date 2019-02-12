/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 10:49:18 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/12 07:09:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "winsize.h"

typedef struct		s_mlximg
{
	void			*ptr;
	unsigned int	*data;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	t_winsize		size;
}					t_mlximg;

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

int					init_mlx(t_mlx *lib, t_winsize *ws);
int					create_mlximage(t_mlx *lib, t_winsize size, t_mlximg *img);
void				destroy_mlx(t_mlx *lib);

#endif
