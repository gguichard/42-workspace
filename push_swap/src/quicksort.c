/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 23:32:50 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/26 23:38:41 by gguichar         ###   ########.fr       */
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
		ps_rot(RA, lst, tmp);
		return (0);
	}
	else
	{
		ps_rot(PB, lst, tmp);
		return (1);
	}
}

static int	partition(int n, t_list **lst, t_list **tmp, int value)
{
	int		index;
	int		pivot;
	int		lst_size;
	int		rot_count;
	t_rot	rot_type;

	index = 0;
	pivot = 0;
	while (n > 0 && !is_gte_value(n, *lst, value))
	{
		part(lst, tmp, value) ? pivot++ : index++;
		n--;
	}
	lst_size = ft_lstsize(*lst);
	rot_count = (lst_size - index <= lst_size / 2) ? lst_size - index : index;
	rot_type = (lst_size - index <= lst_size / 2) ? RA : RRA;
	index = 0;
	while (index < rot_count)
	{
		ps_rot(rot_type, lst, tmp);
		index++;
	}
	return (pivot);
}

static int	sort_special_cases(int n, t_list **lst, t_list **tmp)
{
	if (n <= 3)
	{
		threesort(n, lst, tmp);
		return (1);
	}
	else if (n <= 12)
	{
		insertsort(n, lst, tmp);
		return (1);
	}
	return (0);
}

void		quicksort(int n, t_list **lst)
{
	static t_list	*tmp = NULL;
	int				value;
	int				pivot;
	int				index;

	if (n < 2 || is_sorted(n, *lst) || sort_special_cases(n, lst, &tmp))
		return ;
	value = find_median_pivot(n, *lst);
	pivot = partition(n, lst, &tmp, value);
	quicksort(n - pivot, lst);
	index = 0;
	while (index < pivot)
	{
		ps_rot(PA, lst, &tmp);
		index++;
	}
	quicksort(pivot, lst);
}
