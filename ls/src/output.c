/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 09:12:28 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/28 09:19:19 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

void	show_simple(t_opt *opt, t_flist *lst)
{
	(void)opt;
	while (lst != NULL)
	{
		ft_printf("%s\n", lst->name);
		lst = lst->next;
	}
}
