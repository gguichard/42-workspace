/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 10:51:28 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/11 16:28:17 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"
#include "filler.h"

int	main(int argc, char **argv)
{
	t_filler	filler;
	t_piece		*piece;

	(void)argc;
	(void)argv;
	if (!read_player(&filler))
		return (1);
	filler.board = NULL;
	filler.rows = -1;
	filler.cols = -1;
	while (read_board(&filler))
	{
		piece = parse_piece();
		ft_printf("0 0\n");
	}
	ft_strtab_free(filler.board);
	return (0);
}
