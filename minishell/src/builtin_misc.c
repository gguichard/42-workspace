/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 23:45:43 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/01 11:24:11 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "printf.h"
#include "minishell.h"

void		builtin_exit(int argc, char **argv, t_list **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	exit(0);
}

static int	cd_dir_check(char *path)
{
	struct stat	data;

	if (path == NULL)
		return (UNKNOWN_ERR);
	else if (stat(path, &data) < 0)
		return (NOT_FOUND_ERR);
	else if (!(data.st_mode & S_IXUSR))
		return (NO_EXEC_RIGHTS_ERR);
	else if (!S_ISDIR(data.st_mode))
		return (NOT_DIR_ERR);
	else if (chdir(path) < 0)
		return (UNKNOWN_ERR);
	return (1);
}

void		builtin_cd(int argc, char **argv, t_list **env)
{
	char	*cwd;
	char	*path;
	int		res;

	path = NULL;
	if (argc > 1)
		path = argv[1];
	else
		path = get_env(*env, "HOME");
	if (ft_strequ(path, "-"))
	{
		path = get_env(*env, "OLDPWD");
		ft_printf("%s\n", path);
	}
	res = cd_dir_check(path);
	if (res < 0)
	{
		ft_printf("%s: %s.\n", argv[1], str_error(res));
		return ;
	}
	set_env(env, "OLDPWD", get_env(*env, "PWD"));
	if ((cwd = getcwd(NULL, 0)) != NULL)
	{
		set_env(env, "PWD", cwd);
		free(cwd);
	}
}

void		builtin_echo(int argc, char **argv, t_list **env)
{
	char	*str;
	size_t	index;

	(void)argc;
	(void)env;
	index = 1;
	if (argv[1] != NULL && ft_strequ(argv[1], "-n"))
		index++;
	str = ft_join(&(argv[index]), " ");
	if (index == 2 && str != NULL)
		ft_putstr(str);
	else if (index == 1)
		ft_putendl(str == NULL ? "" : str);
	free(str);
}
