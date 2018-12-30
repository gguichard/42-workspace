/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:36:24 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/30 08:33:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "fdf.h"

static int		parse_point(t_point *point, char **line)
{
	point->z = ft_strtol(*line, line, 10);
	if ((*line)[0] != ',')
		point->color = 0xFFFFFF;
	else
	{
		(*line)++;
		point->color = ft_strtol(*line, line, 16);
	}
	if ((*line)[0] != ' ' && (*line)[0] != '\0')
		return (0);
	while ((*line)[0] == ' ')
		(*line)++;
	return (1);
}

static int		parse_line(t_fdf *fdf, char *line, t_list **lst)
{
	t_point	point;
	t_list	*elem;

	point.x = 0;
	point.y = fdf->rows;
	while (*line != '\0' && (point.x < fdf->cols || fdf->cols < 0))
	{
		if (!parse_point(&point, &line))
			return (0);
		if (!(elem = ft_lstnew(&point, sizeof(t_point))))
			return (0);
		ft_lstadd(lst, elem);
		(point.x)++;
	}
	if (fdf->cols < 0)
		fdf->cols = point.x;
	return (point.x == fdf->cols);
}

static t_point	**tab_from_list(t_fdf *fdf, t_list *lst)
{
	size_t	size;
	t_point	**tab;
	t_point	*point;

	size = fdf->rows * fdf->cols + 1;
	if (!(tab = (t_point **)malloc(size * sizeof(t_point *))))
		return (NULL);
	while (lst != NULL)
	{
		point = (t_point *)lst->content;
		tab[point->y * fdf->cols + point->x] = point;
		lst = lst->next;
	}
	return (tab);
}

static void		free_list(void *content, size_t content_size)
{
	(void)content;
	(void)content_size;
}

int				read_file(const char *name, t_fdf *fdf)
{
	int		fd;
	int		ret;
	char	*line;
	t_list	*lst;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (0);
	ret = 1;
	lst = NULL;
	fdf->cols = -1;
	fdf->rows = 0;
	while (ret && get_next_line(fd, &line) > 0)
	{
		ret = parse_line(fdf, line, &lst);
		free(line);
		(fdf->rows)++;
	}
	close(fd);
	if (ret && !(fdf->points = tab_from_list(fdf, lst)))
		ret = 0;
	ft_lstdel(&lst, &free_list);
	return (ret);
}
