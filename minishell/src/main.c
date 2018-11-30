/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:25:14 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/30 20:51:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "printf.h"
#include "minishell.h"

pid_t		g_child_pid = 0;
t_list		*g_env = NULL;

static void	exit_sig(int sig)
{
	if (g_child_pid > 0)
		kill(g_child_pid, sig);
	ft_putchar('\n');
	if (g_child_pid == 0)
		show_prompt(&g_env);
}

void		show_prompt(t_list **env)
{
	ft_printf("%s:%s%% ", get_env(*env, "USER"), get_env(*env, "PWD"));
}

int			main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	if (!(g_env = setup_env(environ)))
	{
		ft_dprintf(2, "minishell: Unable to read environ.\n");
		return (1);
	}
	signal(SIGINT, &exit_sig);
	while (1)
	{
		show_prompt(&g_env);
		read_input(&g_env);
	}
	return (0);
}
