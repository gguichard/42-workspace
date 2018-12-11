/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 10:51:12 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/11 16:18:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

typedef struct	s_filler
{
	int			player;
	int			rows;
	int			cols;
	char		**board;

}				t_filler;

typedef struct	s_piece
{
	int			width;
	int			height;
	char		**board;
}				t_piece;

/**
** PARSING part
*/
void			*read_player(t_filler *filler);
int				read_board(t_filler *filler);
t_piece		 	*parse_piece(void);

#endif
