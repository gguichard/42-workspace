/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 22:02:45 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/21 09:59:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parse_arg(char *arg, int *number)
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

int			create_list(t_list **lst, int argc, char **argv)
{
	int		index;
	int		value;
	t_list	*back;
	t_list	*elem;

	index = 0;
	back = NULL;
	while (index < argc)
	{
		if (!parse_arg(argv[index], &value)
				|| !(elem = ft_lstnew(&value, sizeof(int))))
		{
			ft_lstfree(lst);
			return (-1);
		}
		if (*lst == NULL)
			*lst = elem;
		if (back != NULL)
			back->next = elem;
		back = elem;
		index++;
	}
	return (index);
}
