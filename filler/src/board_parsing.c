/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 14:50:34 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/12 09:20:43 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include "filler.h"

static int	check_board(t_filler *filler, char *offset)
{
	int	rows;
	int	cols;

	rows = ft_strtol(offset, &offset, 10);
	if (*offset++ != ' ')
		return (0);
	cols = ft_strtol(offset, &offset, 10);
	if (*offset++ != ':' || *offset != '\0')
		return (0);
	if (filler->board == NULL)
	{
		if (!(filler->board = (char **)malloc((rows + 1) * sizeof(char *))))
			return (0);
		filler->board[rows] = NULL;
		filler->cols = cols;
		filler->rows = rows;
		rows = 0;
		while (rows < filler->rows)
		{
			if (!(filler->board[rows] = (char *)malloc(cols + 1)))
				return (0);
			rows++;
		}
	}
	return (filler->rows == rows && filler->cols == cols);
}

static int	valid_board_line(t_filler *filler, const char *line)
{
	int	col;

	if (ft_strlen(line) != (size_t)(4 + filler->cols))
		return (0);
	line += 4;
	col = 0;
	while (line[col] != '\0')
	{
		if (line[col] != '.'
				&& line[col] != 'x' && line[col] != 'X'
				&& line[col] != 'o' && line[col] != 'O')
			return (0);
		col++;
	}
	return (1);
}

static int	read_board_lines(t_filler *filler)
{
	char	*line;
	int		row;

	row = 0;
	while (row < filler->rows)
	{
		if (get_next_line(STDIN_FILENO, &line) <= 0)
			return (0);
		if (!valid_board_line(filler, line))
		{
			free(line);
			return (0);
		}
		ft_memcpy(filler->board[row], line + 4, filler->cols);
		filler->board[row][filler->cols] = '\0';
		free(line);
		row++;
	}
	return (1);
}

int			read_board(t_filler *filler)
{
	char	*line;

	if (get_next_line(STDIN_FILENO, &line) <= 0)
		return (0);
	if (!ft_strnstr(line, "Plateau ", 8) || !check_board(filler, line + 8))
	{
		free(line);
		return (0);
	}
	free(line);
	if (get_next_line(STDIN_FILENO, &line) <= 0)
		return (0);
	if (ft_strlen(line) != (size_t)(4 + filler->cols))
	{
		free(line);
		return (0);
	}
	free(line);
	return (read_board_lines(filler));
}