/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 13:25:06 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/26 23:38:45 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	threesort(int n, t_list **lst, t_list **tmp)
{
	if (is_sorted(n, *lst))
		return ;
	if (!is_sorted(2, *lst))
		ps_rot(SA, lst, tmp);
	else
	{
		ps_rot(RA, lst, tmp);
		ps_rot(SA, lst, tmp);
		ps_rot(RRA, lst, tmp);
	}
	threesort(n, lst, tmp);
}
