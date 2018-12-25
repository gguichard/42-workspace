/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 23:32:50 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/25 13:32:25 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "libft.h"
#include "rotations.h"
#include "push_swap.h"

static int	is_sorted(int n, t_list *lst)
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

static int	is_lte_value(int n, t_list *lst, int value)
{
	while (n > 0)
	{
		if (*((int *)lst->content) > value)
			return (0);
		lst = lst->next;
		n--;
	}
	return (1);
}

static int	is_gt_value(int n, t_list *lst, int value)
{
	while (n > 0)
	{
		if (*((int *)lst->content) <= value)
			return (0);
		lst = lst->next;
		n--;
	}
	return (1);
}

static int	find_pivot(int n, t_list *lst)
{
	int	tab[n];
	int	i;
	int	tmp;

	i = 0;
	while (i < n)
	{
		tab[i] = *((int *)lst->content);
		lst = lst->next;
		i++;
	}
	i = 1;
	while (i < n)
	{
		if (tab[i - 1] > tab[i])
		{
			tmp = tab[i - 1];
			tab[i - 1] = tab[i];
			tab[i] = tmp;
			if (i > 1)
				i -= 1;
			continue ;
		}
		i++;
	}
	tmp = tab[n / 2];
	return (tmp);
}

static int	partition(int n, t_list **lst, t_list **tmp, int value)
{
	int	index;
	int	pivot;
	int	rots;

	index = 0;
	pivot = 0;
	rots = 0;
	while (index < n && !is_gt_value(n - index, *lst, value))
	{
		if (*((int *)(*lst)->content) >= value)
		{
			rotate(lst);
			ft_putendl("ra");
			rots++;
		}
		else
		{
			push(tmp, lst);
			ft_putendl("pb");
			pivot++;
		}
		index++;
	}
	while (rots > 0)
	{
		rev_rotate(lst);
		ft_putendl("rra");
		if (*((int *)(*lst)->content) == value)
		{
			push(tmp, lst);
			ft_putendl("pb");
			pivot++;
		}
		rots--;
	}
	return (pivot);
}

void		quicksort(int n, t_list **lst)
{
	static t_list	*tmp = NULL;
	int				value;
	int				pivot;
	int				index;

	if (n < 2 || is_sorted(n, *lst))
		return ;
	if (n == 2)
	{
		swap(lst);
		ft_putendl("sa");
		return ;
	}
	value = find_pivot(n, *lst);
	if (is_lte_value(n, *lst, value))
		pivot = n;
	else
	{
		pivot = partition(n, lst, &tmp, value);
		quicksort(n - pivot, lst);
		index = 0;
		while (index < pivot)
		{
			push(lst, &tmp);
			ft_putendl("pa");
			index++;
		}
	}
	quicksort(pivot - 1, lst);
}
