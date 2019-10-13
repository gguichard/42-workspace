/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 18:58:56 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/22 19:17:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_DRAW_H
# define LINE_DRAW_H

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

typedef struct	s_vline
{
	int			x0;
	int			x1;
	double		z0;
	double		z1;
	int			x;
	int			y;
	int			z;
}				t_vline;

void			draw_line(t_fdf *fdf, t_pos start, t_pos end);
void			draw_vline(t_fdf *fdf, t_vec3d pos[2], unsigned int color);

#endif
