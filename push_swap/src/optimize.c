/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 00:32:41 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/27 21:40:26 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rotations.h"
#include "push_swap.h"

t_list		**get_rots(void)
{
	static t_list	*rots = NULL;

	return (&rots);
}

static char	*rot_name(t_rot type)
{
	static char	*rots[] = {
		"pa", "pb",
		"sa", "sb", "ss",
		"ra", "rb", "rr",
		"rra", "rrb", "rrr"
	};
	return (rots[type]);
}

void		ps_rot(t_rot type, t_ps *ps)
{
	char	*name;
	t_list	*elem;

	name = rot_name(type);
	if (has_opt(ps->opt, 'v'))
		ft_printf("\nInstruction : %s\n", name);
	else if ((elem = ft_lstnew(name, ft_strlen(name) + 1)) != NULL)
		ft_lstpush(get_rots(), elem);
	(type == PA) ? ps_push(&(ps->lst), &(ps->tmp)) : 0;
	(type == PB) ? ps_push(&(ps->tmp), &(ps->lst)) : 0;
	(type == SA || type == SS) ? ps_swap(&(ps->lst)) : 0;
	(type == SB || type == SS) ? ps_swap(&(ps->tmp)) : 0;
	(type == RA || type == RR) ? ps_rotate(&(ps->lst)) : 0;
	(type == RB || type == RR) ? ps_rotate(&(ps->tmp)) : 0;
	(type == RRA || type == RRR) ? ps_rev_rotate(&(ps->lst)) : 0;
	(type == RRB || type == RRR) ? ps_rev_rotate(&(ps->tmp)) : 0;
	verbose_mode(ps);
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
	t_list	**rots;
	t_list	*prev;
	t_list	*curr;

	rots = get_rots();
	curr = *rots;
	prev = NULL;
	while (curr != NULL && curr->next != NULL)
	{
		if (can_optimize_rot(curr->content, curr->next->content))
		{
			if (prev == NULL)
				*rots = curr->next->next;
			else
				prev->next = curr->next->next;
			curr->next->next = NULL;
			ft_lstfree(&curr);
			curr = *rots;
			prev = NULL;
			continue ;
		}
		prev = curr;
		curr = curr->next;
	}
}
