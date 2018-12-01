/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 09:27:37 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/01 09:54:13 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

char	*expand_str(char *str, t_list **env)
{
	char	*res;
	char	*offset;
	char	*tmp;
	size_t	len;

	res = str;
	if (res[0] == '~')
		res = ft_strreplace_free(res, "~", get_env(*env, "HOME"));
	while ((offset = ft_strchr(res, '$')) != NULL)
	{
		len = 1;
		while (ft_isalnum(offset[len]))
			len++;
		tmp = ft_strsub(offset, 0, len);
		res = ft_strreplace_free(res, tmp, get_env(*env, tmp + 1));
		free(tmp);
	}
	return (res);
}
