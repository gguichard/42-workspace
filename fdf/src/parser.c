/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:36:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/03 12:13:19 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "fdf.h"

static int		parse_pos(t_fdf *fdf, t_pos *pos, char **line)
{
	pos->z = ft_strtol(*line, line, 10);
	if ((*line)[0] != ',')
		pos->color = get_palette_color(fdf, pos->z);
	else
	{
		(*line)++;
		pos->color = ft_strtol(*line, line, 0);
	}
	if ((*line)[0] != ' ' && (*line)[0] != '\0')
		return (0);
	while ((*line)[0] == ' ')
		(*line)++;
	return (1);
}

static int		parse_line(t_fdf *fdf, char *line, t_vector *points)
{
	t_pos	pos;
	t_pos	*ptr;

	pos.x = 0;
	pos.y = fdf->rows;
	while (*line != '\0' && (pos.x < fdf->cols || fdf->cols == 0))
	{
		if (!parse_pos(fdf, &pos, &line))
			return (0);
		ptr = (t_pos *)malloc(sizeof(t_pos));
		if (ptr == NULL)
			return (0);
		ft_memcpy(ptr, &pos, sizeof(t_pos));
		if (!ft_vecpush(points, ptr))
		{
			free(ptr);
			return (0);
		}
		(pos.x)++;
	}
	if (fdf->cols == 0)
		fdf->cols = pos.x;
	return (pos.x == fdf->cols);
}

t_vector		read_file(const char *name, t_fdf *fdf)
{
	t_vector	points;
	int			fd;
	int			ret;
	char		*line;

	ft_memset(&points, 0, sizeof(t_vector));
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (points);
	ret = 1;
	fdf->cols = 0;
	fdf->rows = 0;
	while (ret && get_next_line(fd, &line) > 0)
	{
		ret = parse_line(fdf, line, &points);
		free(line);
		(fdf->rows)++;
	}
	close(fd);
	if (fdf->rows == 0 || fdf->cols == 0)
		ret = 0;
	if (!ret)
		ft_vecfree(&points);
	return (points);
}
