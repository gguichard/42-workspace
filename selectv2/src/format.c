/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 22:09:35 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/05 12:02:35 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "select.h"

t_select_format	get_columns_format(t_select *select)
{
	t_select_format	fmt;
	t_item			*current;

	ft_memset(&fmt, 0, sizeof(t_select_format));
	current = select->cur_items;
	while (current != NULL)
	{
		fmt.col_width = ft_max(fmt.col_width, ft_strlen(current->content));
		current = current->next;
	}
	fmt.col_width += 4;
	return (fmt);
}
