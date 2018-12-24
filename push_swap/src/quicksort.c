/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 23:32:50 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/24 13:43:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rotations.h"
#include "push_swap.h"

static int	is_sorted(int n, int offset, t_list *lst)
{
	int	index;

	index = 0;
	while (index < offset)
	{
		lst = lst->next;
		index++;
	}
	index = 1;
	while (index < n)
	{
		if (*((int *)lst->content) > *((int *)lst->next->content))
			return (0);
		lst = lst->next;
		index++;
	}
	return (1);
}

static int	find_pivot(int n, t_list *lst)
{
	while (n > 1)
	{
		lst = lst->next;
		n--;
	}
	return (*((int *)lst->content));
}

static int	is_lte_value(int n, t_list *lst, int value)
{
	while (n > 1)
	{
		if (*((int *)lst->content) > value)
			return (0);
		lst = lst->next;
		n--;
	}
	return (1);
}

static int	partition(int n, t_list **lst, t_list **tmp, int value)
{
	int	index;
	int	pivot;

	index = 0;
	pivot = 0;
	while (index < n)
	{
		if (*((int *)(*lst)->content) > value)
		{
			rotate(lst);
			ft_putendl("ra");
		}
		else
		{
			push(tmp, lst);
			ft_putendl("pb");
			pivot++;
		}
		index++;
	}
	return (pivot);
}

void		quicksort(int n, t_list **lst)
{
	static t_list	*tmp = NULL;
	int				value;
	int				pivot;
	int				index;

	if (n < 2 || is_sorted(n, 0, *lst))
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
		index = pivot;
		while (index < n)
		{
			rev_rotate(lst);
			ft_putendl("rra");
			index++;
		}
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
