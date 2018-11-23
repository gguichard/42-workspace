/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:16:12 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/23 13:29:22 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

int	sort_by_name(t_flist *f1, t_flist *f2)
{
	return (ft_strcmp(f1->data->d_name, f2->data->d_name));
}
