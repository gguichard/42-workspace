/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:40:20 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/01 00:36:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "printf.h"
#include "get_next_line.h"
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

static char		*wait_cmdline(void)
{
	char	*cmd;
	int		res;

	cmd = NULL;
	if ((res = get_next_line(STDOUT_FILENO, &cmd)) == 0)
	{
		ft_printf("\n");
		exit(0);
	}
	else if (res < 0)
	{
		ft_dprintf(2, "minishell: Unable to read command line.\n");
		return (NULL);
	}
	return (cmd);
}

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
	else if (g_child_pid == 0 && !(execve(path, argv, env_as_str(env))))
	{
		ft_dprintf(2, "minishell: Error when executing %s.\n", path);
		exit(1);
	}
}

static void		interpret_cmd(int argc, char **argv, t_list **env)
{
	size_t	index;
	char	*path;
	int		res;

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
	path = NULL;
	if (!ft_strchr(argv[0], '/'))
		res = search_for_binary(argv[0], env, &path);
	else
	{
		path = ft_strdup(argv[0]);
		res = is_binary_exec(path);
	}
	if (path == NULL)
		ft_dprintf(2, "%s: Command not found.\n", argv[0]);
	else if (res < 0)
		ft_dprintf(2, "%s: %s.\n", path, str_error(res));
	else
		exec_cmd(path, argv, env);
	free(path);
}

static void		process_cmd(char *cmd, t_list **env)
{
	char	**argv;
	int		argc;

	if (!(argv = ft_strsplit(cmd, ' ')))
	{
		ft_dprintf(2, "%s: Command error.\n", cmd);
		return ;
	}
	argc = 0;
	while (argv[argc] != NULL)
		argc++;
	if (argc >= 1)
	{
		ft_strtolower(argv[0]);
		interpret_cmd(argc, argv, env);
	}
	ft_strtab_free(argv);
}

void			read_input(t_list **env)
{
	char	*cmdline;
	char	**cmds;
	char	*cmd;
	size_t	index;

	cmdline = wait_cmdline();
	cmds = ft_strsplit(cmdline, ';');
	free(cmdline);
	if (cmds == NULL)
	{
		ft_dprintf(2, "minishell: Error while parsing commands.\n");
		return ;
	}
	index = 0;
	while (cmds[index] != NULL)
	{
		cmd = ft_strstrim(cmds[index], " \t");
		if (cmd != NULL && cmd[0] != '\0')
			process_cmd(cmd, env);
		free(cmd);
		index++;
	}
	ft_strtab_free(cmds);
}
