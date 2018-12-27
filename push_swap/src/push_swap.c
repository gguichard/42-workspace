/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 13:12:30 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/27 18:00:50 by gguichar         ###   ########.fr       */
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

static void	verbose_mode(t_opt *opt, t_list *lst)
{
	if (!has_opt(opt, 'v'))
		return ;
	while (lst != NULL)
	{
		ft_printf("%d\n", *((int *)lst->content));
		lst = lst->next;
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
	t_opt	*opt;
	t_list	*lst;
	int		n;

	opt = parse_opts(argc, argv, "vh");
	if (has_opt(opt, 'h') || (opt->error != 0 && !ft_isdigit(opt->error)))
		return (show_help(opt));
	if (create_list(&lst, argc - opt->index, argv + opt->index) < 0)
	{
		ft_lstfree(&lst);
		ft_dprintf(2, "Error\n");
		return (0);
	}
	n = ft_lstsize(lst);
	if (n > 1 && !is_sorted(n, lst))
	{
		(n <= 3) ? minsort(n, &lst) : quicksort(n, &lst);
		optimize_rots();
		print_rots();
	}
	verbose_mode(opt, lst);
	ft_lstfree(&lst);
	return (0);
}
