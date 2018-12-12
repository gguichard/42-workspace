/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_iq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:10:47 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/12 23:38:23 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"
#include "filler.h"
#include <math.h>

static void	iq_lock_target(t_filler *filler)
{
	int	row;
	int	col;

	row = 0;
	while (row < filler->rows)
	{
		col = 0;
		while (col < filler->cols)
		{
			if (filler->board[row][col] != '.' 
					&& filler->board[row][col] != filler->player)
			{
				filler->target.x = col;
				filler->target.y = row;
				return ;
			}
			col++;
		}
		row++;
	}
}

static void	iq_piece_pos(t_filler *filler, t_piece *piece)
{
	int	row;
	int	col;
	int	delta;
	int	best_delta;

	row = 0;
	best_delta = 99999;
	while (row < filler->rows)
	{
		col = 0;
		while (col < filler->cols)
		{
			if (check_piece_pos(filler, piece, row, col))
			{
				delta = pow(filler->target.x - col - piece->off_x, 2)
					+ pow(filler->target.y - row - piece->off_y, 2);
				if (delta < best_delta)
				{
					best_delta = delta;
					filler->pos.x = col - piece->off_x;
					filler->pos.y = row - piece->off_y;
				}
			}
			col++;
		}
		row++;
	}
}

void		iq_search_pos(t_filler *filler, t_piece *piece)
{
	if (filler->target.x == -1 && filler->target.y == -1)
		iq_lock_target(filler);
	iq_piece_pos(filler, piece);
}
