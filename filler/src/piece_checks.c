/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 22:19:43 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/13 10:16:51 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"

int	check_piece_pos(t_filler *filler, t_piece *piece, int row, int col)
{
	int		x;
	int		y;
	int		overlap;
	char	map;

	if (row + piece->height >= filler->rows
			|| col + piece->width >= filler->cols)
		return (0);
	overlap = 0;
	y = piece->off_y;
	while (y < piece->height)
	{
		x = piece->off_x;
		while (x < piece->width)
		{
			map = ft_toupper(filler->board[row + y][col + x]);
			if (piece->board[y][x] == '*')
				if ((map != filler->player && map != '.')
						|| (map == filler->player && (++overlap) > 1))
					return (0);
			x++;
		}
		y++;
	}
	return (overlap == 1);
}
