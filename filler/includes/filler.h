/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 10:51:12 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/12 15:30:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct	s_filler
{
	char		player;
	int			rows;
	int			cols;
	char		**board;
	t_pos		pos;
	t_pos		opp_pos;
}				t_filler;

typedef struct	s_piece
{
	int			width;
	int			height;
	char		**board;
	int			off_x;
	int			off_y;
	int			in_x;
}				t_piece;

/*
** PARSING part
*/
void			*read_player(t_filler *filler);
int				read_board(t_filler *filler);
int			 	parse_piece(t_piece *piece);

/*
** FILLER IQ
*/
void			iq_search_pos(t_filler *filler, t_piece *piece);

#endif
