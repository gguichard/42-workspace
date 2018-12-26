/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 23:32:50 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/26 01:27:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "rotations.h"
#include "push_swap.h"

static int	find_median_pivot(int n, t_list *lst)
{
	int	*tab;
	int	index;
	int	pivot;

	if (!(tab = (int *)malloc(sizeof(int) * n)))
		return (-1);
	index = 0;
	while (index < n)
	{
		tab[index] = *((int *)lst->content);
		lst = lst->next;
		index++;
	}
	bubble_sort(n, tab);
	pivot = tab[n / 2];
	free(tab);
	return (pivot);
}

static int	part(t_list **lst, t_list **tmp, int value)
{
	if (*((int *)(*lst)->content) >= value)
	{
		rot(RA, lst, tmp);
		return (0);
	}
	else
	{
		rot(PB, lst, tmp);
		return (1);
	}
}

static int	partition(int n, t_list **lst, t_list **tmp, int value)
{
	int	index;
	int	pivot;

	index = 0;
	pivot = 0;
	while (n > 0)
	{
		part(lst, tmp, value) ? pivot++ : index++;
		n--;
	}
	while (index > 0)
	{
		rot(RRA, lst, tmp);
		if (*((int *)(*lst)->content) == value)
		{
			rot(PB, lst, tmp);
			pivot++;
		}
		index--;
	}
	return (pivot);
}

void		sort_simple(int n, t_list **lst, t_list **tmp)
{
	if (!is_sorted(2, *lst))
		rot(SA, lst, tmp);
	else
	{
		rot(RA, lst, tmp);
		rot(SA, lst, tmp);
		rot(RRA, lst, tmp);
	}
	if (!is_sorted(n, *lst))
		sort_simple(n, lst, tmp);
}

void		quicksort(int n, t_list **lst)
{
	static t_list	*tmp = NULL;
	int				value;
	int				pivot;
	int				index;

	if (n < 2 || is_sorted(n, *lst))
		return ;
	if (n <= 3)
	{
		sort_simple(n, lst, &tmp);
		return ;
	}
	value = find_median_pivot(n, *lst);
	pivot = partition(n, lst, &tmp, value);
	quicksort(n - pivot, lst);
	index = 0;
	while (index < pivot)
	{
		rot(PA, lst, &tmp);
		index++;
	}
	quicksort(pivot - 1, lst);
}
