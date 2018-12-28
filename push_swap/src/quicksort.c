/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 23:32:50 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/28 13:43:11 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
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

static int	part(t_ps *ps, int value)
{
	if (*((int *)(ps->lst)->content) >= value)
	{
		ps_rot(RA, ps);
		return (0);
	}
	else
	{
		ps_rot(PB, ps);
		return (1);
	}
}

static int	partition(int n, t_ps *ps, int value)
{
	int		index;
	int		pivot;
	int		lst_size;
	int		rot_count;
	t_rot	rot_type;

	index = 0;
	pivot = 0;
	while (n > 0 && !is_gte_value(n, ps->lst, value))
	{
		part(ps, value) ? pivot++ : index++;
		n--;
	}
	lst_size = ft_lstsize(ps->lst);
	rot_count = (lst_size - index <= lst_size / 2) ? lst_size - index : index;
	rot_type = (lst_size - index <= lst_size / 2) ? RA : RRA;
	index = 0;
	while (index < rot_count)
	{
		ps_rot(rot_type, ps);
		index++;
	}
	return (pivot);
}

static int	sort_special_cases(int n, t_ps *ps)
{
	if (n <= 3)
	{
		threesort(n, ps);
		return (1);
	}
	else if (n <= 12)
	{
		insertsort(n, ps);
		return (1);
	}
	return (0);
}

void		quicksort(int n, t_ps *ps)
{
	int	value;
	int	pivot;
	int	index;

	if (n < 2 || sort_special_cases(n, ps))
		return ;
	value = find_median_pivot(n, ps->lst);
	pivot = partition(n, ps, value);
	if (!is_sorted(n, ps->lst))
		quicksort(n - pivot, ps);
	index = 0;
	while (index < pivot)
	{
		ps_rot(PA, ps);
		index++;
	}
	if (!is_sorted(pivot, ps->lst))
		quicksort(pivot, ps);
}
