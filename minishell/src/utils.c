/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:00:43 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/01 00:45:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

char	*str_error(int err)
{
	if (err == NOT_FOUND_ERR)
		return ("No such file or directory");
	if (err == NOT_REG_ERR)
		return ("Is not a file");
	if (err == NOT_DIR_ERR)
		return ("Is not a dir");
	if (err == NO_EXEC_RIGHTS_ERR)
		return ("Permission denied");
	return ("Unknown error");
}

char	**env_as_str(t_list **lst)
{
	char	*str;
	t_list	*beg;

	str = NULL;
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
