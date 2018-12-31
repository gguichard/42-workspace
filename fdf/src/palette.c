/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 02:45:40 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/31 03:18:40 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "fdf.h"

static int	parse_color(t_fdf *fdf, char *line)
{
	t_color	color;
	t_list	*elem;

	color.max = ft_strtol(line, &line, 10);
	if (line[0] != ' ')
		return (0);
	color.value = ft_strtol(line, &line, 16);
	if (line[0] != '\0')
		return (0);
	if (!(elem = ft_lstnew(&color, sizeof(t_color))))
		return (0);
	ft_lstpush(&(fdf->palette), elem);
	return (1);
}

int			parse_palette(const char *file, t_fdf *fdf)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	ret = 1;
	while (ret && get_next_line(fd, &line) > 0)
	{
		if (line[0] != '#' && !parse_color(fdf, line))
			ret = 0;
		free(line);
	}
	if (!ret)
		ft_lstfree(&(fdf->palette));
	return (ret);
}

int			get_palette_color(t_fdf *fdf, int z)
{
	t_list	*curr;
	t_color	*color;

	curr = fdf->palette;
	while (curr != NULL)
	{
		color = (t_color *)curr->content;
		if (z <= color->max)
			return (color->value);
		curr = curr->next;
	}
	return (0xFFFFFF);
}
