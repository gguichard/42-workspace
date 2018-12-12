/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 10:51:28 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/12 23:21:57 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"
#include "filler.h"

int	main(void)
{
	t_filler	filler;
	t_piece		piece;

	if (!read_player(&filler))
		return (1);
	filler.board = NULL;
	filler.rows = -1;
	filler.cols = -1;
	filler.pos.x = -1;
	filler.pos.y = -1;
	filler.target.x = -1;
	filler.target.y = -1;
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
		ft_strtab_free(piece.board);
	}
	ft_strtab_free(filler.board);
	return (0);
}
