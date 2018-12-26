/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 02:06:40 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/26 23:38:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "push_swap.h"

static void	setup_tab_list(int n, t_list **lst, t_list **tmp, int *tab)
{
	int		index;
	t_list	*curr;

	index = 3;
	while (index < n)
	{
		ps_rot(PB, lst, tmp);
		index++;
	}
	threesort(3, lst, tmp);
	index = 0;
	curr = *lst;
	while (index < 3)
	{
		tab[index] = *((int *)curr->content);
		curr = curr->next;
		index++;
	}
	if (n >= 5 && is_sorted(2, *tmp))
		ps_rot(SB, lst, tmp);
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

static void	rotate_to(int index, t_list **lst, t_list **tmp)
{
	static int	offset = 0;

	if (offset < index)
	{
		while (offset < index)
		{
			ps_rot(RA, lst, tmp);
			offset++;
		}
	}
	else
	{
		while (offset > index)
		{
			ps_rot(RRA, lst, tmp);
			offset--;
		}
	}
}

void		insertsort(int n, t_list **lst, t_list **tmp)
{
	int	index;
	int	*tab;
	int	j;

	if (!(tab = (int *)malloc(n * sizeof(int))))
		return ;
	setup_tab_list(n, lst, tmp, tab);
	index = 3;
	while (index < n)
	{
		j = 0;
		while (j < index && tab[j] < *((int *)(*tmp)->content))
			j++;
		create_tab_hole(index, tab, j);
		tab[j] = *((int *)(*tmp)->content);
		rotate_to(j, lst, tmp);
		ps_rot(PA, lst, tmp);
		index++;
	}
	rotate_to(0, lst, tmp);
	free(tab);
}
