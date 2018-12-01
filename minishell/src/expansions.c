/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 09:27:37 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/01 17:12:48 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static char	*expand_env_var(char *res, t_list **env)
{
	size_t	len;
	int		brackets;
	char	*sub;
	char	*name;
	char	*offset;

	while ((offset = ft_strchr(res, '$')) != NULL)
	{
		brackets = offset[1] == '{';
		len = brackets + 1;
		while (ft_isalnum(offset[len]))
			len++;
		if (brackets && offset[len] != '}')
		{
			ft_dprintf(2, "minishell: %s.\n", "Bad brackets");
			return (NULL);
		}
		sub = ft_strsub(offset, 0, len + brackets);
		name = ft_strsub(offset, 1 + brackets, len - 1 - brackets);
		res = ft_strreplace_free(res, sub, get_env(*env, name, ""));
		free(sub);
		free(name);
	}
	return (res);
}

char		*expand_str(char *str, t_list **env)
{
	char	*res;

	res = str;
	if (res[0] == '~')
		res = ft_strreplace_free(res, "~", get_env(*env, "HOME", ""));
	if (res == NULL)
		return (NULL);
	return (expand_env_var(res, env));
}
