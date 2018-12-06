/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:36:24 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/06 20:16:48 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "fdf.h"

static void	pos_clean(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

static int	parse_line(const char *line, int row, t_list **lst)
{
	int		col;
	t_pos	pos;
	t_list	*elem;

	col = 0;
	while (*line != '\0')
	{
		pos.x = col;
		pos.y = row;
		pos.z = ft_strtol(line, NULL, 10);
		line += ft_llsize(pos.z);
		if (*line != ' ' && *line != '\0')
			return (0);
		if (!(elem = ft_lstnew(&pos, sizeof(pos))))
			return (0);
		ft_lstpush(lst, elem);
		while (*line == ' ')
			line++;
		col++;
	}
	return (1);
}

int			read_file(const char *name)
{
	int		fd;
	char	*line;
	int		row;
	t_list	*lst;
	
	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (0);
	row = 0;
	lst = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(parse_line(line, row, &lst)))
		{
			ft_lstdel(&lst, &pos_clean);
			close(fd);
			return (0);
		}
		row++;
	}
	close(fd);
	return (1);
}
