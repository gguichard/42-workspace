/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 13:25:06 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/26 14:02:58 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	threesort(int n, t_list **lst, t_list **tmp)
{
	if (is_sorted(n, *lst))
		return ;
	if (!is_sorted(2, *lst))
		rot(SA, lst, tmp);
	else
	{
		rot(RA, lst, tmp);
		rot(SA, lst, tmp);
		rot(RRA, lst, tmp);
	}
	threesort(n, lst, tmp);
}
