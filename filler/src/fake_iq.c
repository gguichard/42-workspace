/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_iq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:10:47 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/12 21:39:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"
#include "filler.h"

static void	iq_first_pos(t_filler *filler)
{
	int	row;
	int	col;

	row = 0;
	while (row < filler->rows)
	{
		col = 0;
		while (col < filler->cols)
		{
			if (filler->board[row][col] == filler->player)
			{
				filler->pos.x = col;
				filler->pos.y = row;
				return ;
			}
			col++;
		}
		row++;
	}
}

/*static int	check_piece_overlap(t_filler *filler
		, t_piece *piece, int row, int col)
{
	int		overlap;
	int		y;
	int		x;
	char	map;

	// todo: check map bounds
	overlap = 0;
	y = 0;
	while (y < piece->height)
	{
		x = 0;
		while (x < piece->width)
		{
			if (piece->board[y][x] == '*')
			{
				map = ft_toupper(filler->board[row + y][col + x]);
				if (map != filler->player && map != '.')
					return (0);
				else if (map == filler->player && (++overlap) > 1)
					return (0);
			}
			x++;
		}
		y++;
	}
	return (overlap == 1);
}*/

static void	iq_piece_pos(t_filler *filler, t_piece *piece)
{
	(void)filler;
	(void)piece;
}

void		iq_search_pos(t_filler *filler, t_piece *piece)
{
	if (filler->pos.x != -1 && filler->pos.y != -1)
		iq_piece_pos(filler, piece);
	else
	{
		iq_first_pos(filler);
		filler->pos.x -= piece->off_x;
		filler->pos.y -= piece->off_y;
	}
}
