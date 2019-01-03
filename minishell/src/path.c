/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:06:53 by gguichar          #+#    #+#             */
/*   Updated: 2019/01/03 15:10:58 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "printf.h"
#include "minishell.h"

static int	check_dirs_exec(char *path)
{
	char	*offset;
	char	*tmp;

	offset = path;
	while ((tmp = ft_strchr(offset, '/')) != NULL)
	{
		*tmp = '\0';
		if (access(path, X_OK) < 0)
		{
			*tmp = '/';
			return (0);
		}
		*tmp = '/';
		offset = tmp + 1;
	}
	return (1);
}

int			is_binary_exec(char *path, int check_dirs)
{
	struct stat	data;

	if (check_dirs && !check_dirs_exec(path))
		return (NO_EXEC_RIGHTS_ERR);
	if (stat(path, &data) < 0)
		return (NOT_FOUND_ERR);
	if (!S_ISREG(data.st_mode))
		return (NOT_REG_ERR);
	if (access(path, X_OK) < 0)
		return (NO_EXEC_RIGHTS_ERR);
	return (1);
}

int			search_for_binary(const char *name, t_list **env, char **path)
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
		res = is_binary_exec(tmp, 0);
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
