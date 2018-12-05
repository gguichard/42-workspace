/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:09:19 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/05 09:52:57 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>
#include "ft_select.h"

extern t_select	*g_select;

int				ft_tputchar(int c)
{
	return (write(STDERR_FILENO, &c, 1));
}

void			clean_exit(int code)
{
	reset_term();
	clean_search();
	clean_choices();
	exit(code);
}

void			handle_signal(int sig)
{
	char	*str;

	if (sig == SIGWINCH)
	{
		init_select();
		print_select();
	}
	else if (sig == SIGCONT)
	{
		setup_term();
		init_select();
		print_select();
	}
	else if (sig == SIGTSTP)
	{
		reset_term();
		signal(SIGTSTP, SIG_DFL);
		if (!(str = ft_strnew(1)))
			return ;
		str[0] = g_select->def.c_cc[VSUSP];
		ioctl(STDIN_FILENO, TIOCSTI, str);
		free(str);
	}
}
