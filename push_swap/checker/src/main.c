/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:38:40 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/19 17:26:00 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*check_args(int size, char **args)
{
	int		index;
	char	*tmp;
	int		number;
	t_list	*lst;
	t_list	*back;
	t_list	*elem;

	index = 0;
	lst = NULL;
	back = NULL;
	while (index < size)
	{
		tmp = args[index];
		number = ft_strtol(tmp, &tmp, 10);
		if (tmp[0] != '\0')
			return (ft_lstfree(&lst));
		if (!(elem = ft_lstnew(&number, sizeof(int))))
			return (ft_lstfree(&lst));
		if (lst == NULL)
			lst = elem;
		elem->next = back;
		back = elem;
		index++;
	}
	return (lst);
}

int		main(int argc, char **argv)
{
	if (!check_args(argc - 1, argv + 1))
	{
		ft_dprintf(2, "Error\n");
		return (1);
	}
	(void)argc;
	(void)argv;
	return (0);
}
