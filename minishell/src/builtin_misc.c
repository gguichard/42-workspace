/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 23:45:43 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/01 00:03:57 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "printf.h"
#include "minishell.h"

void	builtin_exit(int argc, char **argv, t_list **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	exit(0);
}

void	builtin_cd(int argc, char **argv, t_list **env)
{
	char	*cwd;
	char	*path;

	path = NULL;
	if (argc > 1)
		path = argv[1];
	else
		path = get_env(*env, "HOME");
	if (ft_strequ(path, "-"))
		path = get_env(*env, "OLDPWD");
	if (path != NULL && chdir(path) < 0)
	{
		ft_printf("%s: %s.\n", argv[1], str_error(NOT_FOUND_ERR));
		return ;
	}
	set_env(env, "OLDPWD", get_env(*env, "PWD"));
	if ((cwd = getcwd(NULL, 0)) != NULL)
	{
		set_env(env, "PWD", cwd);
		free(cwd);
	}
}

void	builtin_echo(int argc, char **argv, t_list **env)
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
