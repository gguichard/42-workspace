/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 10:51:28 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/13 10:39:16 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "printf.h"
#include "filler.h"

static void	init_filler(t_filler *filler)
{
	filler->board = NULL;
	filler->old_board = NULL;
	filler->rows = -1;
	filler->cols = -1;
	filler->pos.x = -1;
	filler->pos.y = -1;
	filler->target.x = -1;
	filler->target.y = -1;
}

static void	save_old_board(t_filler *filler)
{
	int	row;

	if (filler->old_board == NULL)
	{
		if (!(filler->old_board
					= (char **)malloc((filler->rows + 1) * sizeof(char *))))
			return ;
		row = 0;
		while (row < filler->rows)
		{
			if (!(filler->old_board[row]
						= (char *)malloc((filler->cols + 1) * sizeof(char))))
			{
				ft_strtab_free(filler->old_board);
				return ;
			}
			row++;
		}
		filler->old_board[row] = NULL;
	}
	row = 0;
	while (row < filler->rows)
	{
		ft_memcpy(filler->old_board[row], filler->board[row], filler->cols + 1);
		row++;
	}
}

int			main(void)
{
	t_filler	filler;
	t_piece		piece;

	if (!read_player(&filler))
		return (1);
	init_filler(&filler);
	while (read_board(&filler))
	{
		ft_memset(&piece, 0, sizeof(piece));
		if (!parse_piece(&piece))
		{
			ft_strtab_free(piece.board);
			break ;
		}
		iq_search_pos(&filler, &piece);
		ft_printf("%d %d\n", filler.pos.y, filler.pos.x);
		save_old_board(&filler);
		ft_strtab_free(piece.board);
	}
	ft_strtab_free(filler.board);
	ft_strtab_free(filler.old_board);
	return (0);
}
