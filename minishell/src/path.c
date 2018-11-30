/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:06:53 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/30 14:14:00 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include "libft.h"
#include "printf.h"
#include "minishell.h"

static int	has_binary(const char *name, const char *path)
{
	DIR				*dir;
	struct dirent	*data;

	if (!(dir = opendir(path)))
		return (0);
	while ((data = readdir(dir)) != NULL)
	{
		if (ft_strequ(name, data->d_name))
			return (1);
	}
	closedir(dir);
	return (0);
}

char		*search_for_binary(const char *name, t_list **env)
{
	char	*path;
	char	**folders;
	size_t	index;
	char	*full_path;

	path = get_env(*env, PATH_ENV);
	if (path == NULL)
		return (NULL);
	folders = ft_strsplit(path, ':');
	if (!(folders))
		return (NULL);
	index = 0;
	while (folders[index] != NULL)
	{
		if (has_binary(name, folders[index]))
		{
			full_path = NULL;
			ft_asprintf(&full_path, "%s/%s", folders[index], name);
			ft_strfree_tab(folders);
			return (full_path);
		}
		index++;
	}
	return (ft_strfree_tab(folders));
}
