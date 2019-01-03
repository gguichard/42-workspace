/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 10:02:22 by gguichar          #+#    #+#             */
/*   Updated: 2019/01/03 11:16:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "printf.h"
#include "minishell.h"

extern pid_t	g_child_pid;

t_cmd			g_builtin[] =
{
	{"exit", &builtin_exit},
	{"cd", &builtin_cd},
	{"echo", &builtin_echo},
	{"env", &builtin_env},
	{"setenv", &builtin_setenv},
	{"unsetenv", &builtin_unsetenv},
	{NULL, NULL}
};

static void		exec_cmd(char *path, char **argv, t_list **env)
{
	g_child_pid = fork();
	if (g_child_pid < 0)
		ft_dprintf(2, "%s: Unable to fork.", path);
	else if (g_child_pid > 0)
	{
		waitpid(g_child_pid, NULL, 0);
		g_child_pid = 0;
	}
	else if (g_child_pid == 0)
	{
		execve(path, argv, env_as_str(env));
		ft_dprintf(2, "minishell: Error when executing %s.\n", path);
		exit(1);
	}
}

static int		exec_builtin(int argc, char **argv, t_list **env)
{
	size_t	index;

	index = 0;
	while (g_builtin[index].name != NULL)
	{
		if (ft_strequ(argv[0], g_builtin[index].name))
		{
			(g_builtin[index]).exec(argc, argv, env);
			return (1);
		}
		index++;
	}
	return (0);
}

static void		interpret_cmd(int argc, char **argv, t_list **env)
{
	char	*path;
	int		res;

	if (exec_builtin(argc, argv, env))
		return ;
	path = NULL;
	if (!ft_strchr(argv[0], '/')
			&& get_env(*env, "PATH", " ")[0] != '\0')
		res = search_for_binary(argv[0], env, &path);
	else
	{
		path = ft_strdup(argv[0]);
		res = is_binary_exec(path, 1);
	}
	if (path == NULL)
		ft_dprintf(2, "%s: Command not found.\n", argv[0]);
	else if (res < 0)
		ft_dprintf(2, "%s: %s.\n", path, str_error(res));
	else
		exec_cmd(path, argv, env);
	free(path);
}

static int		expand_args(char **argv, t_list **env)
{
	int		argc;
	char	*tmp;

	argc = 0;
	while (argv[argc] != NULL)
	{
		if (!(tmp = expand_str(argv[argc], env)))
			return (-1);
		argv[argc] = tmp;
		argc++;
	}
	return (argc);
}

void			process_cmd(char *cmd, t_list **env)
{
	char	**argv;
	int		argc;

	if (!(argv = ft_strsplit(cmd, ' ')))
	{
		ft_dprintf(2, "%s: Command error.\n", cmd);
		return ;
	}
	argc = expand_args(argv, env);
	if (argc >= 1)
	{
		ft_strtolower(argv[0]);
		interpret_cmd(argc, argv, env);
	}
	ft_strtab_free(argv);
}
