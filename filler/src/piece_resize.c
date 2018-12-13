/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_resize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:31:11 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/13 18:07:26 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "filler.h"

void		piece_fix_height(t_piece *piece)
{
	int	row;

	row = piece->height - 1;
	while (row >= 0 && !ft_strchr(piece->board[row], '*'))
	{
		free(piece->board[row]);
		piece->board[row] = NULL;
		piece->height--;
		row--;
	}
	piece->off_y = 0;
	while (piece->height > 0 && !ft_strchr(piece->board[0], '*'))
	{
		free(piece->board[0]);
		row = 0;
		while (row < piece->height)
		{
			piece->board[row] = piece->board[row + 1];
			row++;
		}
		piece->off_y++;
		piece->height--;
	}
}

static void	piece_update_width(t_piece *piece, int min_col, int max_col)
{
	int		row;
	char	*tmp;

	piece->width = (max_col + 1) - min_col;
	row = 0;
	while (row < piece->height)
	{
		tmp = piece->board[row];
		if (min_col > 0)
			ft_memcpy(tmp, tmp + min_col, piece->width);
		piece->board[row][piece->width] = '\0';
		row++;
	}
}

void		piece_fix_width(t_piece *piece)
{
	int			row;
	int			max_col;
	int			min_col;
	const char	*tmp;

	row = 0;
	max_col = 0;
	min_col = piece->width;
	while (row < piece->height)
	{
		tmp = ft_strchr(piece->board[row], '*');
		if (tmp != NULL)
			min_col = ft_min(min_col, (int)(tmp - piece->board[row]));
		tmp = ft_strrchr(piece->board[row], '*');
		if (tmp != NULL)
			max_col = ft_max(max_col, (int)(tmp - piece->board[row]));
		row++;
	}
	piece->off_x = min_col;
	piece_update_width(piece, min_col, max_col);
}
