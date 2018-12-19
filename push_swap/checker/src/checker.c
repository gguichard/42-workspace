/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:03:34 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/19 19:26:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

static int	apply_instruction(char *name, t_list **a, t_list **b)
{
}

int			apply_sets(int count, t_list **a, t_list **b)
{
	char	*line;

	while (count > 0)
	{
		if (get_next_line(STDIN_FILENO, &line) <= 0)
			return (0);
		if (!apply_instruction(line, a, b))
			return (0);
		count--;
	}
	return (1);
}
