/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:08:45 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/13 17:08:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include "filler.h"

static int	valid_piece_line(t_piece *piece, const char *line)
{
	int	index;

	index = 0;
	while (index < piece->width)
	{
		if (line[index] == '\0' || (line[index] != '.' && line[index] != '*'))
			return (0);
		index++;
	}
	return (line[index] == '\0');
}

static int	parse_piece_size(t_piece *piece, char *offset)
{
	int	index;

	piece->height = ft_strtol(offset, &offset, 10);
	if (*offset++ != ' ')
		return (0);
	piece->width = ft_strtol(offset, &offset, 10);
	if (*offset++ != ':' || *offset != '\0')
		return (0);
	if (!(piece->board = (char **)malloc((piece->height + 1) * sizeof(char *))))
		return (0);
	piece->board[piece->height] = NULL;
	index = 0;
	while (index < piece->height)
	{
		if (!(piece->board[index] = (char *)malloc(piece->width + 1)))
			return (0);
		index++;
	}
	return (1);
}

static int	parse_piece_lines(t_piece *piece)
{
	int		index;
	char	*line;

	index = 0;
	while (index < piece->height)
	{
		if (get_next_line(STDIN_FILENO, &line) <= 0)
			return (0);
		if (!valid_piece_line(piece, line))
		{
			free(line);
			return (0);
		}
		ft_memcpy(piece->board[index], line, piece->width);
		piece->board[index][piece->width] = '\0';
		free(line);
		index++;
	}
	return (1);
}

int			parse_piece(t_piece *piece)
{
	char	*line;

	if (get_next_line(STDIN_FILENO, &line) <= 0)
		return (0);
	if (!ft_strnstr(line, "Piece ", 6) || !parse_piece_size(piece, line + 6))
	{
		free(line);
		return (0);
	}
	free(line);
	if (!parse_piece_lines(piece))
		return (0);
	piece_fix_height(piece);
	piece_fix_width(piece);
	return (1);
}
