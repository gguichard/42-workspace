/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 08:58:02 by wta               #+#    #+#             */
/*   Updated: 2018/11/17 14:15:31 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include "libft.h"

typedef unsigned short	t_ushort;

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct	s_shape
{
	t_ushort	data;
	int			width;
	int			height;
	int			x_min;
	int			x_max;
	t_pos		pos;
}				t_shape;

typedef struct	s_info
{
	int			size;
	int			count;
	t_shape		**shapes;
	t_ushort	board[16];
}				t_info;

void			ft_exiterror(void);

int				count_active_bits(unsigned char byte);

int				check_line(const char *str);

int				is_overlapping(t_info *info, t_shape *shape);

int				is_shape_valid(t_shape *shape);

t_shape			**get_shapes(int fd);

void			resolve(t_info *info);

void			print_shapes(t_info *info);

#endif
