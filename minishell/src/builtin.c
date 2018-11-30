/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 09:34:38 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/30 19:08:31 by gguichar         ###   ########.fr       */
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
	if (path != NULL && chdir(path) < 0)
	{
		ft_printf("%s: %s.\n", argv[1], str_error(NOT_FOUND_ERR));
		return ;
	}
	if ((cwd = getcwd(NULL, 0)) != NULL)
	{
		set_env(env, "PWD", cwd);
		free(cwd);
	}
}

void	builtin_env(int argc, char **argv, t_list **env)
{
	t_list	*lst;

	(void)argc;
	(void)argv;
	lst = *env;
	while (lst != NULL)
	{
		ft_printf("%s=%s\n"
				, ((t_env *)(lst->content))->name
				, ((t_env *)(lst->content))->value);
		lst = lst->next;
	}
}

void	builtin_setenv(int argc, char **argv, t_list **env)
{
	char	*value;

	if (argc <= 1)
	{
		ft_dprintf(2, "%s: Missing var name.\n", argv[0]);
		return ;
	}
	value = "0";
	if (argc >= 3)
		value = argv[2];
	if (!(set_env(env, argv[1], value)))
	{
		ft_dprintf(2, "%s: Unable to set var value.\n", argv[0]);
		return ;
	}
	ft_printf("%s: Set to %s.\n", argv[1], value);
}

void	builtin_unsetenv(int argc, char **argv, t_list **env)
{
	if (argc <= 1)
	{
		ft_dprintf(2, "%s: Missing var name.\n", argv[0]);
		return ;
	}
	else if (!(unset_env(env, argv[1])))
	{
		ft_dprintf(2, "%s: Not a valid var name.\n", argv[1]);
		return ;
	}
	ft_printf("%s: Removed.\n", argv[1]);
}
