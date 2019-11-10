/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 01:07:39 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/10 15:02:28 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include "vec2.h"
#include "window.h"
#include "line_draw.h"

static inline void	step_line(t_line *line)
{
	int	tmp;

	tmp = 2 * line->err;
	if (tmp >= -line->dy)
	{
		line->err -= line->dy;
		line->x += line->sx;
	}
	if (tmp <= line->dx)
	{
		line->err += line->dx;
		line->y += line->sy;
	}
}

static inline void	draw_line_bresenham(t_line_ctx ctx
	, t_vec2i start, t_vec2i end, uint32_t color)
{
	t_line	line;

	line.x0 = start.x;
	line.y0 = start.y;
	line.x1 = end.x;
	line.y1 = end.y;
	line.dx = ft_abs(line.x1 - line.x0);
	line.dy = ft_abs(line.y1 - line.y0);
	line.sx = line.x0 < line.x1 ? 1 : -1;
	line.sy = line.y0 < line.y1 ? 1 : -1;
	line.x = line.x0;
	line.y = line.y0;
	line.err = line.dx - line.dy;
	while (line.x != line.x1 || line.y != line.y1)
	{
		if (line.x >= 0 && line.y >= 0
			&& line.x < ctx.win_width && line.y < ctx.win_height)
			ctx.pixels[line.y * ctx.win_width + line.x] = color;
		step_line(&line);
	}
}

void				draw_line(t_line_ctx ctx, t_vec2i start, t_vec2i end
	, uint32_t color)
{
	if ((start.x < 0 && end.x < 0)
		|| (start.y < 0 && end.y < 0)
		|| (start.x >= ctx.win_width && end.x >= ctx.win_width)
		|| (start.y >= ctx.win_height && end.y >= ctx.win_height))
		return ;
	draw_line_bresenham(ctx, start, end, color);
}
