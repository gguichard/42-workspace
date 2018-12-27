/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 13:42:11 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/27 21:35:37 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include "options.h"

typedef struct	s_ps
{
	t_opt		*opt;
	t_list		*lst;
	t_list		*tmp;
}				t_ps;

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

void			verbose_mode(t_ps *ps);

t_list			**get_rots(void);
void			ps_rot(t_rot type, t_ps *ps);
void			optimize_rots(void);

/*
** SORTING part.
*/
int				is_gte_value(int n, t_list *lst, int value);
int				is_sorted(int n, t_list *lst);
void			bubble_sort(int n, int *tab);

void			minsort(int n, t_ps *ps);
void			quicksort(int n, t_ps *ps);
void			threesort(int n, t_ps *ps);
void			insertsort(int n, t_ps *ps);

#endif
