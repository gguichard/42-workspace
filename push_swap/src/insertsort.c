/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 02:06:40 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/28 02:14:49 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "push_swap.h"

static void	setup_tab_list(int n, int left, t_ps *ps, int *tab)
{
	int		index;
	t_list	*curr;

	index = left;
	while (index < n)
	{
		ps_rot(PB, ps);
		index++;
	}
	if (ft_lstsize(ps->lst) == (unsigned int)left)
		minsort(left, ps);
	else
		threesort(left, ps);
	index = 0;
	curr = ps->lst;
	while (index < left)
	{
		tab[index] = *((int *)curr->content);
		curr = curr->next;
		index++;
	}
}

static void	create_tab_hole(int n, int *tab, int at)
{
	int	index;

	index = n - 1;
	while (index >= at)
	{
		tab[index + 1] = tab[index];
		index--;
	}
}

static void	rotate_to(int index, t_ps *ps)
{
	static int	offset = 0;

	if (offset < index)
	{
		while (offset < index)
		{
			ps_rot(RA, ps);
			offset++;
		}
	}
	else
	{
		while (offset > index)
		{
			ps_rot(RRA, ps);
			offset--;
		}
	}
}

void		insertsort(int n, t_ps *ps)
{
	int	*tab;
	int	left;
	int	index;
	int	j;

	if (!(tab = (int *)malloc(n * sizeof(int))))
		return ;
	left = ft_min(3, n);
	setup_tab_list(n, left, ps, tab);
	index = left;
	while (index < n)
	{
		j = 0;
		while (j < index && tab[j] < *((int *)(ps->tmp)->content))
			j++;
		create_tab_hole(index, tab, j);
		tab[j] = *((int *)(ps->tmp)->content);
		rotate_to(j, ps);
		ps_rot(PA, ps);
		index++;
	}
	rotate_to(0, ps);
	free(tab);
}
