/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 13:12:30 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/22 12:54:59 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "parsing.h"
#include "push_swap.h"

/*void	quick_sort(t_list *lst)
{
}*/

int		main(int argc, char **argv)
{
	t_list	*lst;

	if (create_list(&lst, argc - 1, argv + 1) < 0)
	{
		ft_dprintf(2, "Error\n");
		return (0);
	}
	return (0);
}
