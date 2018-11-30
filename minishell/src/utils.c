/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:00:43 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/30 15:49:57 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

char	**env_as_str(t_list **lst)
{
	char	*str;
	t_list	*beg;

	str = ft_strdup("");
	beg = *lst;
	while (beg != NULL)
	{
		str = ft_strjoin_free(str, ((t_env *)(beg->content))->name);
		str = ft_strjoin_free(str, "=");
		str = ft_strjoin_free(str, ((t_env *)(beg->content))->value);
		str = ft_strjoin_free(str, ";");
		beg = beg->next;
	}
	return (ft_strsplit(str, ';'));
}
