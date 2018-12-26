/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 00:32:41 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/26 23:39:01 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "rotations.h"
#include "push_swap.h"

static char	*rot_name(t_rot type)
{
	if (type == PA)
		return ("pa");
	if (type == PB)
		return ("pb");
	if (type == SA)
		return ("sa");
	if (type == SB)
		return ("sb");
	if (type == SS)
		return ("ss");
	if (type == RA)
		return ("ra");
	if (type == RB)
		return ("rb");
	if (type == RR)
		return ("rr");
	if (type == RRA)
		return ("rra");
	if (type == RRB)
		return ("rrb");
	if (type == RRR)
		return ("rrr");
	return ("");
}

t_list		**get_rots(void)
{
	static t_list	*rots = NULL;

	return (&rots);
}

void		ps_rot(t_rot type, t_list **lst, t_list **tmp)
{
	char	*name;
	t_list	*elem;

	name = rot_name(type);
	if (!(elem = ft_lstnew(name, ft_strlen(name) + 1)))
		return ;
	ft_lstpush(get_rots(), elem);
	(type == PA) ? ps_push(lst, tmp) : 0;
	(type == PB) ? ps_push(tmp, lst) : 0;
	(type == SA || type == SS) ? ps_swap(lst) : 0;
	(type == SB || type == SS) ? ps_swap(tmp) : 0;
	(type == RA || type == RR) ? ps_rotate(lst) : 0;
	(type == RB || type == RR) ? ps_rotate(tmp) : 0;
	(type == RRA || type == RRR) ? ps_rev_rotate(lst) : 0;
	(type == RRB || type == RRR) ? ps_rev_rotate(tmp) : 0;
}

static int	can_optimize_rot(const char *curr, const char *next)
{
	if ((ft_strequ(curr, "pa") && ft_strequ(next, "pb"))
		|| (ft_strequ(curr, "pb") && ft_strequ(next, "pa")))
		return (1);
	if ((ft_strequ(curr, "ra") && ft_strequ(next, "rra"))
		|| (ft_strequ(curr, "rra") && ft_strequ(next, "ra")))
		return (1);
	if ((ft_strequ(curr, "rb") && ft_strequ(next, "rrb"))
		|| (ft_strequ(curr, "rrb") && ft_strequ(next, "rb")))
		return (1);
	return (0);
}

void		optimize_rots(void)
{
	t_list	*prev;
	t_list	*rots;

	prev = NULL;
	rots = *(get_rots());
	while (rots != NULL && rots->next != NULL)
	{
		if (can_optimize_rot(rots->content, rots->next->content))
		{
			if (prev == NULL)
				*(get_rots()) = rots->next->next;
			else
				prev->next = rots->next->next;
			rots->next->next = NULL;
			ft_lstfree(&rots);
			rots = *(get_rots());
			prev = NULL;
			continue ;
		}
		prev = rots;
		rots = rots->next;
	}
}
