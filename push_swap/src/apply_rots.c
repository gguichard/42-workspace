/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_rots.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:03:34 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/27 17:52:21 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"
#include "rotations.h"
#include "checker.h"

static int	apply_rot(char *name, t_checker *checker)
{
	int	ret;

	ret = 0;
	if (ft_strequ("sa", name) || ft_strequ("ss", name))
		ret = ps_swap(&(checker->a));
	if (ft_strequ("sb", name) || ft_strequ("ss", name))
		ret = ps_swap(&(checker->b));
	if (ft_strequ("pa", name))
		ret = ps_push(&(checker->a), &(checker->b));
	if (ft_strequ("pb", name))
		ret = ps_push(&(checker->b), &(checker->a));
	if (ft_strequ("ra", name) || ft_strequ("rr", name))
		ret = ps_rotate(&(checker->a));
	if (ft_strequ("rb", name) || ft_strequ("rr", name))
		ret = ps_rotate(&(checker->b));
	if (ft_strequ("rra", name) || ft_strequ("rrr", name))
		ret = ps_rev_rotate(&(checker->a));
	if (ft_strequ("rrb", name) || ft_strequ("rrr", name))
		ret = ps_rev_rotate(&(checker->b));
	return (ret);
}

int			apply_rots(t_checker *checker)
{
	int		ret;
	char	*line;

	while ((ret = get_next_line(checker->fd, &line)) > 0)
	{
		if (!apply_rot(line, checker))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	return (ret == 0);
}

int			check_lists(t_checker *checker)
{
	t_list	*prev;
	t_list	*lst;

	if (checker->b != NULL)
		return (0);
	if (checker->a != NULL)
	{
		prev = checker->a;
		lst = prev->next;
		while (lst != NULL)
		{
			if (*((int *)lst->content) < *((int *)prev->content))
				return (0);
			prev = lst;
			lst = lst->next;
		}
	}
	return (1);
}
