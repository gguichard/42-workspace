/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 02:06:40 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/26 02:42:20 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

static int	is_minval(int n, t_list *lst)
{
	int	value;

	value = *((int *)lst->content);
	while (n > 1)
	{
		lst = lst->next;
		if (*((int *)lst->content) < value)
			return (0);
		n--;
	}
	return (1);
}

void		insertsort(int n, t_list **lst, t_list **tmp)
{
	int	index;
	int	count;

	index = 0;
	while (index < n && !is_sorted(n - index, *lst))
	{
		count = 0;
		while (!is_minval(n - index, *lst))
		{
			rot(RA, lst, tmp);
			count++;
		}
		rot(PB, lst, tmp);
		while (count > 0)
		{
			rot(RRA, lst, tmp);
			count--;
		}
		index++;
	}
	while (index > 0)
	{
		rot(PA, lst, tmp);
		index--;
	}
}
