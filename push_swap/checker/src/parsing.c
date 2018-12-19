/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 22:02:45 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/19 23:28:17 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "checker.h"

static int	parse_number(char *arg, int *number)
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

t_list		*create_list(t_checker *checker)
{
	int		number;
	t_list	*lst;
	t_list	*back;
	t_list	*elem;

	lst = NULL;
	back = NULL;
	while (checker->argc > 0)
	{
		if (!parse_number(checker->argv[0], &number)
				|| !(elem = ft_lstnew(&number, sizeof(int))))
			return (ft_lstfree(&lst));
		if (lst == NULL)
			lst = elem;
		if (back != NULL)
			back->next = elem;
		back = elem;
		checker->argc--;
		checker->argv++;
	}
	return (lst);
}
