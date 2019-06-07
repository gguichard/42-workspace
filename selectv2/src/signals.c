/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:49:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/07 16:00:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>
#include "select.h"

extern t_select	*g_select;

void			handle_job_signals(int signo)
{
	t_select	*select;

	select = g_select;
	if (signo == SIGCONT)
	{
		signal(SIGTSTP, handle_job_signals);
		setup_term(select);
		print_select_items(select);
	}
	else if (signo == SIGTSTP)
	{
		signal(SIGTSTP, SIG_DFL);
		reset_term(select);
		ioctl(STDIN_FILENO, TIOCSTI, &select->def_term.c_cc[VSUSP]);
	}
}

void			handle_resize_signal(int signo)
{
	t_select	*select;

	select = g_select;
	if (signo == SIGWINCH)
	{
		update_winsize(select);
		print_select_items(select);
	}
}

void			handle_common_signal(int signo)
{
	t_select	*select;

	select = g_select;
	reset_term(select);
	close(select->tty_fd);
	ft_lstfree(&select->hotkeys);
	ft_memdel((void **)&select->def_items);
	exit(signo);
}
