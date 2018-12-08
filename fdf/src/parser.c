/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:36:24 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/08 11:01:16 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "fdf.h"

static void	point_clean(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

static int	parse_point(t_point *point, char **line)
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

static int	parse_line(const char *line, int row, t_list **lst)
{
	t_point	point;
	t_list	*elem;

	point.x = 0;
	point.y = row;
	while (*line != '\0')
	{
		if (!(parse_point(&point, (char **)&line)))
			return (0);
		if (!(elem = ft_lstnew(&point, sizeof(point))))
			return (0);
		ft_lstadd(lst, elem);
		(point.x)++;
	}
	return (1);
}

t_list		*read_file(const char *name)
{
	int		fd;
	char	*line;
	int		row;
	t_list	*lst;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	row = 0;
	lst = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(parse_line(line, row, &lst)))
		{
			free(line);
			close(fd);
			return (ft_lstdel(&lst, &point_clean));
		}
		free(line);
		row++;
	}
	close(fd);
	return (lst);
}
