/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 11:36:14 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/04 20:15:56 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>
#include "ft_select.h"

extern	t_select	*g_select;

void	handle_resize(int signal)
{
	(void)signal;
	init_select();
	print_select();
}

void	handle_pause(int sig)
{
	char	*str;

	(void)sig;
	reset_term();
	signal(SIGTSTP, SIG_DFL);
	if (!(str = ft_strnew(1)))
		return ;
	str[0] = g_select->def.c_cc[VSUSP];
	ioctl(STDIN_FILENO, TIOCSTI, str);
	free(str);
}

void	handle_continue(int signal)
{
	(void)signal;
	init_term();
	init_select();
	print_select();
}

void	handle_signal(int signal)
{
	reset_term();
	clean_choices();
	exit(signal);
}
