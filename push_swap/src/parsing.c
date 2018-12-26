/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 22:02:45 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/26 18:18:30 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parse_nb(char *str, int *store)
{
	long int	value;
	char		*endptr;

	value = ft_strtol(str, &endptr, 10);
	if (*endptr != '\0' || value != (int)value)
		return (0);
	*store = (int)value;
	return (1);
}

static int	is_duplicated(int value, t_list *lst)
{
	while (lst != NULL)
	{
		if (*((int *)lst->content) == value)
			return (1);
		lst = lst->next;
	}
	return (0);
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
		if (!parse_nb(argv[index], &value) || is_duplicated(value, *lst))
			return (-1);
		if (!(elem = ft_lstnew(&value, sizeof(value))))
			return (-1);
		if (*lst == NULL)
			*lst = elem;
		if (back != NULL)
			back->next = elem;
		back = elem;
		index++;
	}
	return (index);
}
