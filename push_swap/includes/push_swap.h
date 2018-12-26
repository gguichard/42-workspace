/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 13:42:11 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/26 01:16:43 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

/*
** ROTATIONS.
*/
typedef enum	e_rot
{
	PA, PB,
	SA, SB, SS,
	RA, RB, RR,
	RRA, RRB, RRR
}				t_rot;

t_list	**get_rots(void);
void	rot(t_rot type, t_list **lst, t_list **tmp);
void	optimize_rots(void);

/*
** SORTING part.
*/
int		is_sorted(int n, t_list *lst);
void	bubble_sort(int n, int *tab);
void	quicksort(int n, t_list **lst);

#endif
