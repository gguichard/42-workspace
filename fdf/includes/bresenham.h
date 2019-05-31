/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 18:58:56 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/31 18:59:35 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRESENHAM_H
# define BRESENHAM_H

# include "fdf.h"

typedef struct	s_line
{
	int			x0;
	int			y0;
	int			z0;
	int			c0;
	int			x1;
	int			y1;
	int			z1;
	int			c1;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			x;
	int			y;
	int			z;
	int			err;
}				t_line;

void			draw_line(t_fdf *fdf, t_pos start, t_pos end);

#endif
