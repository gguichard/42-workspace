/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:36:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/01/01 21:15:19 by gguichar         ###   ########.fr       */
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
		pos->color = ft_strtol(*line, line, 16);
	}
	if ((*line)[0] != ' ' && (*line)[0] != '\0')
		return (0);
	while ((*line)[0] == ' ')
		(*line)++;
	return (1);
}

static int		parse_line(t_fdf *fdf, char *line, t_list **lst)
{
	t_pos	pos;
	t_list	*elem;

	pos.x = 0;
	pos.y = fdf->rows;
	while (*line != '\0' && (pos.x < fdf->cols || fdf->cols == 0))
	{
		if (!parse_pos(fdf, &pos, &line))
			return (0);
		if (!(elem = ft_lstnew(&pos, sizeof(t_pos))))
			return (0);
		ft_lstadd(lst, elem);
		(pos.x)++;
	}
	if (fdf->cols == 0)
		fdf->cols = pos.x;
	return (pos.x == fdf->cols);
}

static t_pos	*tab_from_list(t_fdf *fdf, t_list *lst)
{
	t_pos	*tab;
	t_pos	*pos;

	if (!(tab = (t_pos *)malloc(fdf->rows * fdf->cols * sizeof(t_pos))))
		return (NULL);
	while (lst != NULL)
	{
		pos = (t_pos *)lst->content;
		ft_memcpy(&(tab[pos->y * fdf->cols + pos->x]), pos, sizeof(t_pos));
		lst = lst->next;
	}
	return (tab);
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
	fdf->cols = 0;
	fdf->rows = 0;
	while (ret && get_next_line(fd, &line) > 0)
	{
		ret = parse_line(fdf, line, &lst);
		free(line);
		(fdf->rows)++;
	}
	close(fd);
	if (fdf->rows == 0 || fdf->cols == 0)
		ret = 0;
	if (ret && !(fdf->pos = tab_from_list(fdf, lst)))
		ret = 0;
	ft_lstfree(&lst);
	return (ret);
}
