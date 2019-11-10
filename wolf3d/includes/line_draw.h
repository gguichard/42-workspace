/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 18:58:56 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/10 15:02:51 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_DRAW_H
# define LINE_DRAW_H

# include <stdint.h>
# include "vec2.h"

typedef struct	s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			x;
	int			y;
	int			err;
}				t_line;

typedef struct	s_line_ctx
{
	int			win_width;
	int			win_height;
	uint32_t	*pixels;
}				t_line_ctx;

void			draw_line(t_line_ctx ctx, t_vec2i start, t_vec2i end
	, uint32_t color);

#endif
