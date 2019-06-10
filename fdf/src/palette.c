/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 02:45:40 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/10 20:05:13 by gguichar         ###   ########.fr       */
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

t_error		parse_palette(const char *file, t_fdf *fdf)
{
	t_error	err;
	int		fd;
	int		ret;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		err = ERR_ERRNO;
	else
	{
		err = ERR_NOERROR;
		while (err == ERR_NOERROR && (ret = get_next_line(fd, &line)) > 0)
		{
			if (line[0] != '#' && !parse_color(fdf, line))
				err = ERR_WRONGPALETTEFILE;
			free(line);
		}
		if (ret == -1)
			err = ERR_ERRNO;
		if (err != ERR_NOERROR)
			ft_lstfree(&(fdf->palette));
	}
	return (err);
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
