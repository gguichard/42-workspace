/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minsort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 14:03:20 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/28 13:44:03 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

static int	lstmax_value(int n, t_list *lst)
{
	int	max;

	max = *((int *)lst->content);
	while (n > 1)
	{
		lst = lst->next;
		if (*((int *)lst->content) > max)
			max = *((int *)lst->content);
		n--;
	}
	return (max);
}

void		minsort(int n, t_ps *ps)
{
	int	max;

	max = lstmax_value(n, ps->lst);
	if (*((int *)(ps->lst)->content) == max)
		ps_rot(RA, ps);
	else if (*((int *)(ps->lst)->next->content) == max)
		ps_rot(RRA, ps);
	else
	{
		ps_rot(SA, ps);
		return ;
	}
	if (!is_sorted(n, ps->lst))
		minsort(n, ps);
}
