/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 13:56:03 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/03 16:23:43 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "select.h"
#include "items.h"

static int	error(char *arg, char *message)
{
	ft_dprintf(STDERR_FILENO, "%s: %s\n", arg, message);
	return (1);
}

int			main(int argc, char **argv)
{
	t_select	select;

	if (argc < 2)
		return (error(argv[0], "please specify at least one choice"));
	ft_memset(&select, 0, sizeof(t_select));
	if (setup_term(&select) == -1)
		return (error(argv[0], "unable to init term"));
	select.def_items = create_items(argc - 1, argv + 1);
	if (select.def_items == NULL)
	{
		apply_termios(&select.def_term);
		return (error(argv[0], "memory allocation error"));
	}
	free(select.def_items);
	apply_termios(&select.def_term);
	return (0);
}
