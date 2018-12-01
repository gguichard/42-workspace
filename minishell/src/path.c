/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:06:53 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/01 16:11:01 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "printf.h"
#include "minishell.h"

int	is_binary_exec(const char *path)
{
	struct stat	data;

	if (stat(path, &data) < 0)
		return (NOT_FOUND_ERR);
	if (!S_ISREG(data.st_mode))
		return (NOT_REG_ERR);
	if (!(data.st_mode & S_IXUSR))
		return (NO_EXEC_RIGHTS_ERR);
	return (1);
}

int	search_for_binary(const char *name, t_list **env, char **path)
{
	char	**folders;
	size_t	index;
	char	*tmp;
	int		res;

	folders = ft_strsplit(get_env(*env, "PATH", ""), ':');
	if (folders == NULL)
		return (0);
	index = 0;
	while (folders[index] != NULL)
	{
		if (ft_asprintf(&tmp, "%s/%s", folders[index], name) < 0)
			break ;
		res = is_binary_exec(tmp);
		if (res != NOT_FOUND_ERR)
		{
			ft_strtab_free(folders);
			*path = tmp;
			return (res);
		}
		free(tmp);
		index++;
	}
	ft_strtab_free(folders);
	return (0);
}
