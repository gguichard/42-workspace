/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 13:12:30 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/23 13:16:07 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "parsing.h"
#include "options.h"
#include "rotations.h"
#include "push_swap.h"

void	find_pivot(int n, t_list **lst)
{
	(void)n;
	(void)lst;
}

int		partition(int n, t_list **lst, int pivot, t_list **tmp)
{
	int	index;
	int	total;

	index = 0;
	total = 0;
	while (index < n)
	{
		if (*((int *)(*lst)->content) > pivot)
		{
			rotate(lst);
			ft_putendl("ra");
		}
		else
		{
			push(tmp, lst);
			ft_putendl("pb");
			total++;
		}
		index++;
	}
	return (total);
}

void	quicksort(int n, t_list **lst)
{
	static t_list	*tmp = NULL;
	int				pivot;
	int				index;

	if (n <= 1)
		return ;
	find_pivot(n, lst);
	pivot = partition(n, lst, *((int *)(*lst)->content), &tmp);
	rev_rotate(&tmp);
	ft_putendl("rrb");
	index = 0;
	while (index < (n - pivot))
	{
		rev_rotate(lst);
		ft_putendl("rra");
		index++;
	}
	while (tmp != NULL)
	{
		push(lst, &tmp);
		ft_putendl("pa");
	}
	quicksort(pivot - 1, lst);
	index = 0;
	while (index < pivot)
	{
		rotate(lst);
		ft_putendl("ra");
		index++;
	}
	quicksort(n - pivot, lst);
	index = 0;
	while (index < pivot)
	{
		rev_rotate(lst);
		ft_putendl("rra");
		index++;
	}
}

int	main(int argc, char **argv)
{
	t_opt	*opt;
	t_list	*lst;

	opt = parse_opts(argc, argv, "vh");
	if (has_opt(opt, 'h'))
	{
		ft_printf("USAGE: push_swap [options] <numbers>\n\n");
		ft_printf("OPTIONS:\n");
		ft_printf("  -v\tEnable verbose mode\n");
		ft_printf("  -h\tShow this help\n");
		return (0);
	}
	if (create_list(&lst, argc - opt->index, argv + opt->index) < 0)
	{
		ft_dprintf(2, "Error\n");
		return (0);
	}
	quicksort(ft_lstsize(lst), &lst);
	if (has_opt(opt, 'v'))
	{
		while (lst != NULL)
		{
			ft_printf("%d\n", *((int *)lst->content));
			lst = lst->next;
		}
	}
	return (0);
}
