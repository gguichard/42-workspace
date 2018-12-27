/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minsort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 14:03:20 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/27 17:50:05 by gguichar         ###   ########.fr       */
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

void		minsort(int n, t_list **lst)
{
	int	max;

	if (is_sorted(n, *lst))
		return ;
	max = lstmax_value(n, *lst);
	if (*((int *)(*lst)->content) == max)
		ps_rot(RA, lst, NULL);
	else if (*((int *)(*lst)->next->content) == max)
		ps_rot(RRA, lst, NULL);
	else
	{
		ps_rot(SA, lst, NULL);
		return ;
	}
	minsort(n, lst);
}
