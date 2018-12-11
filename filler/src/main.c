/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 10:51:28 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/11 17:48:36 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"
#include "filler.h"

int	main(int argc, char **argv)
{
	t_filler	filler;
	t_piece		piece;

	(void)argc;
	(void)argv;
	if (!read_player(&filler))
		return (1);
	filler.board = NULL;
	filler.rows = -1;
	filler.cols = -1;
	while (read_board(&filler))
	{
		ft_memset(&piece, 0, sizeof(piece));
		if (parse_piece(&piece))
		{
			// todo: place piece
			ft_printf("8 2\n");
		}
		ft_strtab_free(piece.board);
	}
	ft_strtab_free(filler.board);
	return (0);
}
