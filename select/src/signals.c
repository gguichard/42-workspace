/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 11:36:14 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/04 17:47:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include "ft_select.h"

void	handle_resize(int signal)
{
	(void)signal;
	init_select();
	print_select();
}

void	handle_pause(int signal)
{
	(void)signal;
	reset_term();
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
