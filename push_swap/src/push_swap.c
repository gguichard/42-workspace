/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 13:12:30 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/23 16:21:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "parsing.h"
#include "options.h"
#include "rotations.h"
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

static void	quicksort(int n, t_list **lst)
{
	(void)n;
	(void)lst;
}

int			main(int argc, char **argv)
{
	t_opt	*opt;
	t_list	*lst;

	opt = parse_opts(argc, argv, "vh");
	if (has_opt(opt, 'h') || opt->error != 0)
		return (show_help(opt));
	if (create_list(&lst, argc - opt->index, argv + opt->index) < 0)
	{
		ft_dprintf(2, "Error\n");
		return (0);
	}
	quicksort(ft_lstsize(lst), &lst);
	verbose_mode(opt, lst);
	ft_lstfree(&lst);
	return (0);
}
