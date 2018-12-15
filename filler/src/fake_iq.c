/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_iq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:10:47 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/15 10:41:16 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "printf.h"
#include "libft.h"
#include "filler.h"

static void	iq_search_target(t_filler *filler)
{
	int		row;
	int		col;
	char	map;

	row = 0;
	while (row < filler->rows)
	{
		col = 0;
		while (col < filler->cols)
		{
			map = ft_toupper(filler->board[row][col]);
			if ((map == filler->opp && filler->old_board == NULL) ||
					(map == filler->opp && map != filler->old_board[row][col]))
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

	row = -1;
	best_delta = INT_MAX;
	while (++row < filler->rows)
	{
		col = -1;
		while (++col < filler->cols)
		{
			if (check_piece_pos(filler, piece, row, col))
			{
				delta = ft_pow(filler->target.x - col, 2)
					+ ft_pow(filler->target.y - row, 2);
				if (delta < best_delta)
				{
					best_delta = delta;
					filler->pos.x = col - piece->off_x;
					filler->pos.y = row - piece->off_y;
				}
			}
		}
	}
}

void		iq_search_pos(t_filler *filler, t_piece *piece)
{
	iq_search_target(filler);
	iq_piece_pos(filler, piece);
}
