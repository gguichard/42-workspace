/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:40:20 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/30 16:18:29 by gguichar         ###   ########.fr       */
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
	int		res;

	cmd = NULL;
	if ((res = get_next_line(STDOUT_FILENO, &cmd)) == 0)
	{
		ft_printf("\n");
		exit(0);
	}
	else if (res < 0)
	{
		ft_dprintf(2, "minishell: Unable to read from command line.\n");
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
		ft_dprintf(2, "minishell: Error when executing %s.\n", argv[0]);
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
		ft_dprintf(2, "%s: Command not found.\n", argv[0]);
		return ;
	}
	exec_cmd(path, argv, env);
	free(path);
}

void		show_prompt(t_list **env)
{
	char	*cmd;
	char	**argv;
	int		argc;

	ft_printf("%s:%s%% ", get_env(*env, "USER"), get_env(*env, "PWD"));
	if ((cmd = read_cmd()) != NULL && cmd[0] != '\0')
	{
		if (!(argv = ft_strsplit(cmd, ' ')))
		{
			ft_dprintf(2, "%s: Command error.\n", cmd);
			return ;
		}
		free(cmd);
		argc = 0;
		while (argv[argc] != NULL)
			argc++;
		interpret_cmd(argc, argv, env);
		ft_strfree_tab(argv);
	}
}
