/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:40:20 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/01 11:56:49 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "printf.h"
#include "get_next_line.h"
#include "minishell.h"

static char	*wait_cmdline(void)
{
	char	*cmd;
	int		res;

	cmd = NULL;
	if ((res = get_next_line(STDIN_FILENO, &cmd)) == 0)
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

void		read_input(t_list **env)
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
