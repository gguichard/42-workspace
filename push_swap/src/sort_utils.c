/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:09:26 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/28 13:39:58 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

int		is_gte_value(int n, t_list *lst, int value)
{
	while (n > 0)
	{
		if (*((int *)lst->content) < value)
			return (0);
		lst = lst->next;
		n--;
	}
	return (1);
}

int		is_sorted(int n, t_list *lst)
{
	while (n > 1)
	{
		if (*((int *)lst->content) > *((int *)lst->next->content))
			return (0);
		lst = lst->next;
		n--;
	}
	return (1);
}

void	bubble_sort(int n, int *tab)
{
	int	index;
	int	tmp;

	index = 1;
	while (index < n)
	{
		if (tab[index] >= tab[index - 1])
			index++;
		else
		{
			tmp = tab[index - 1];
			tab[index - 1] = tab[index];
			tab[index] = tmp;
			if (index > 1)
				index--;
		}
	}
}
