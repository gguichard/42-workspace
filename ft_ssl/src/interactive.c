/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 19:09:16 by gguichar          #+#    #+#             */
/*   Updated: 2020/02/28 09:52:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"
#include "ft_ssl.h"

static int	interactive_cmd(const char *prefix, const char *input
	, int *last_ret)
{
	char	**argv;
	int		argc;
	int		ret;

	if (input[0] == '\0')
		return (1);
	else if (ft_strequ(input, "exit") || ft_strequ(input, "quit"))
	{
		*last_ret = 0;
		return (1);
	}
	argv = ft_strssplit(input, " \t");
	if (argv == NULL)
	{
		ft_dprintf(STDERR_FILENO, "unexpected error\n");
		return (0);
	}
	argc = ft_strtab_count(argv);
	ret = 1;
	if (argc > 0)
		ret = exec_command(prefix, argc, argv);
	ft_strtab_free(argv);
	return (ret);
}

int			interactive_mode(const char *prefix)
{
	char	*line;
	int		alive;
	int		ret;

	alive = 1;
	ret = 1;
	while (alive)
	{
		write(STDOUT_FILENO, "FT_SSL> ", 8);
		line = NULL;
		alive = get_next_line(STDIN_FILENO, &line);
		if (alive == 1)
		{
			ret = interactive_cmd(prefix, line, &ret);
			free(line);
		}
		else if (alive == -1)
		{
			ft_dprintf(STDERR_FILENO, "unable to read from standard input\n");
			return (0);
		}
	}
	if (alive == 0)
		write(STDOUT_FILENO, "exit\n", 5);
	return (ret);
}
