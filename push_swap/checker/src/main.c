/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:38:40 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/19 19:09:17 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "checker.h"

static int		check_number(char *arg, int *number)
{
	long int	res;

	res = ft_strtol(arg, &arg, 10);
	if (*arg != '\0')
		return (0);
	if (res != (int)res)
		return (0);
	*number = (int)res;
	return (1);
}

static t_list	*check_args(int size, char **args)
{
	int		index;
	int		number;
	t_list	*lst;
	t_list	*back;
	t_list	*elem;

	index = 0;
	lst = NULL;
	back = NULL;
	while (index < size)
	{
		if (!check_number(args[index], &number)
				|| !(elem = ft_lstnew(&number, sizeof(int))))
			return (ft_lstfree(&lst));
		if (lst == NULL)
			lst = elem;
		elem->next = back;
		back = elem;
		index++;
	}
	return (lst);
}

int				main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;

	if (argc > 1 && !(a = check_args(argc - 1, argv + 1)))
	{
		ft_dprintf(2, "Error\n");
		return (1);
	}
	b = NULL;
	if (!apply_sets(argc - 1, &a, &b))
	{
		ft_dprintf(2, "KO\n");
		return (1);
	}
	ft_printf("OK\n");
	return (0);
}
