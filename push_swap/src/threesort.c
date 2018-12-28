/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 13:25:06 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/28 13:43:30 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	threesort(int n, t_ps *ps)
{
	if (!is_sorted(2, ps->lst))
		ps_rot(SA, ps);
	else
	{
		ps_rot(RA, ps);
		ps_rot(SA, ps);
		ps_rot(RRA, ps);
	}
	if (!is_sorted(n, ps->lst))
		threesort(n, ps);
}
