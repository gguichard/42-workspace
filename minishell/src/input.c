/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:40:20 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/30 15:04:03 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "printf.h"
#include "get_next_line.h"
#include "minishell.h"

t_cmd		g_builtin[] =
{
	{"exit", &builtin_exit},
	{"cd", &builtin_cd},
	{"env", &builtin_env},
	{"setenv", &builtin_setenv},
	{"unsetenv", &builtin_unsetenv},
	{NULL, NULL}
};

static char	*read_cmd(void)
{
	char	*cmd;

	cmd = NULL;
	if (get_next_line(STDOUT_FILENO, &cmd) < 0)
	{
		ft_dprintf(2, "minishell: unable to read from command line\n");
		return (NULL);
	}
	return (cmd);
}

static void	exec_cmd(char *path, char **argv, t_list **env)
{
	pid_t	pid;

	pid = fork();
	if (pid != 0)
		waitpid(pid, NULL, 0);
	else if (!(execve(path, argv, env_as_str(env))))
	{
		ft_dprintf(2, "minishell: error when executing: %s\n", argv[0]);
		exit(1);
	}
}

static void	interpret_cmd(int argc, char **argv, t_list **env)
{
	size_t	index;
	char	*path;

	index = 0;
	while (g_builtin[index].name != NULL)
	{
		if (ft_strequ(argv[0], g_builtin[index].name))
		{
			(g_builtin[index]).exec(argc, argv, env);
			return ;
		}
		index++;
	}
	if (!(path = search_for_binary(argv[0], env)))
	{
		ft_dprintf(2, "minishell: command not found: %s\n", argv[0]);
		return ;
	}
	exec_cmd(path, argv, env);
	free(path);
}

void	show_prompt(t_list **env)
{
	char	*cmd;
	char	**argv;
	int		argc;

	ft_printf("$> ");
	if ((cmd = read_cmd()) != NULL)
	{
		if (!(argv = ft_strsplit(cmd, ' ')))
		{
			ft_dprintf(2, "minishell: command error: %s\n", cmd);
			return ;
		}
		argc = 0;
		while (argv[argc] != NULL)
			argc++;
		interpret_cmd(argc, argv, env);
	}
}
