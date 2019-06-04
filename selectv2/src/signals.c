/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:49:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/04 16:25:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>
#include "select.h"

extern t_select	*g_select;

void			handle_signal(int sig)
{
	t_select	*select;

	select = g_select;
	if (sig == SIGWINCH)
	{
		update_winsize(select);
		print_items(select);
	}
	else if (sig == SIGCONT)
	{
		signal(SIGTSTP, handle_signal);
		setup_term(select);
		print_items(select);
	}
	else if (sig == SIGTSTP)
	{
		signal(SIGTSTP, SIG_DFL);
		reset_term(select);
		ioctl(STDIN_FILENO, TIOCSTI, &select->def_term.c_cc[VSUSP]);
	}
}
