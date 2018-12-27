/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 13:25:06 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/27 21:32:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	threesort(int n, t_ps *ps)
{
	if (is_sorted(n, ps->lst))
		return ;
	if (!is_sorted(2, ps->lst))
		ps_rot(SA, ps);
	else
	{
		ps_rot(RA, ps);
		ps_rot(SA, ps);
		ps_rot(RRA, ps);
	}
	threesort(n, ps);
}
