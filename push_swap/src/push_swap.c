/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 13:12:30 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/28 18:06:29 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "parsing.h"
#include "options.h"
#include "push_swap.h"

static int	show_help(t_opt *opt)
{
	if (opt->error != 0)
		ft_dprintf(2, "push_swap: illegal option -- %c\n", opt->error);
	ft_printf("USAGE: push_swap [options] <numbers>\n\n");
	ft_printf("OPTIONS:\n");
	ft_printf("  -v\tEnable verbose mode\n");
	ft_printf("  -h\tShow this help\n");
	return (0);
}

void		verbose_mode(t_ps *ps)
{
	t_list	*lst;
	t_list	*tmp;

	if (!has_opt(ps->opt, 'v'))
		return ;
	lst = ps->lst;
	tmp = ps->tmp;
	ft_printf("%-10s %s", "Pile A", "Pile B\n");
	while (lst != NULL || tmp != NULL)
	{
		ft_printf("%-10s %s\n"
				, lst == NULL ? "" : ft_itoa(*((int *)lst->content))
				, tmp == NULL ? "" : ft_itoa(*((int *)tmp->content)));
		if (lst != NULL)
			lst = lst->next;
		if (tmp != NULL)
			tmp = tmp->next;
	}
}

static void	print_rots(void)
{
	t_list	**rots;
	t_list	*curr;
	t_list	*next;

	rots = get_rots();
	curr = *rots;
	while (curr != NULL)
	{
		next = curr->next;
		ft_putendl(curr->content);
		free(curr->content);
		free(curr);
		curr = next;
	}
	*rots = NULL;
}

int			main(int argc, char **argv)
{
	t_ps	ps;
	int		n;

	ps.opt = parse_opts(argc, argv, "vh");
	if (has_opt(ps.opt, 'h')
			|| (ps.opt->error != 0 && !ft_isdigit(ps.opt->error))
			|| argc - ps.opt->index <= 0)
		return (show_help(ps.opt));
	if (create_list(&(ps.lst), argc - ps.opt->index, argv + ps.opt->index) < 0)
		ft_dprintf(2, "Error\n");
	else
	{
		ps.tmp = NULL;
		n = ft_lstsize(ps.lst);
		if (n > 1 && !is_sorted(n, ps.lst))
		{
			verbose_mode(&ps);
			(n <= 3) ? minsort(n, &ps) : quicksort(n, &ps);
			optimize_rots();
			print_rots();
			ft_lstfree(&(ps.tmp));
		}
	}
	ft_lstfree(&(ps.lst));
	return (0);
}
