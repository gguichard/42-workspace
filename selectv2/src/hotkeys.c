/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotkeys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 11:51:11 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/04 12:33:03 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "hotkeys.h"

void	add_hotkey(t_list **hotkeys, int type, const char *buffer
	, void (*hook_fn)(int))
{
	t_hotkey	hotkey;
	t_list		*elem;

	hotkey.type = type;
	hotkey.buffer = buffer;
	hotkey.hook_fn = hook_fn;
	elem = ft_lstnew(&hotkey, sizeof(t_hotkey));
	if (elem == NULL)
		return ;
	ft_lstadd(hotkeys, elem);
}

int		hotkey_match(t_list *hotkeys, const char *buffer)
{
	size_t		len;
	t_list		*cur;
	t_hotkey	*hotkey;

	len = ft_strlen(buffer);
	cur = hotkeys;
	while (cur != NULL)
	{
		hotkey = (t_hotkey *)cur->content;
		if (ft_strequ(hotkey->buffer, buffer))
		{
			hotkey->hook_fn(hotkey->type);
			return (hotkey->type);
		}
		cur = cur->next;
	}
	return (-1);
}
