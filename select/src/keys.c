/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 22:25:10 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/04 12:13:01 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"
#include "ft_select.h"

extern t_select	*g_select;

static void		select_choice(t_choice **current)
{
	(*current)->selected = !(*current)->selected;
}

static void		quit_nav(void)
{
	reset_term();
	exit(0);
}

void			handle_keys(char *buf)
{
	static t_choice	*current = NULL;

	if (current == NULL)
		current = g_select->head;
	if (buf[0] == ' ')
		select_choice(&current);
	if (buf[0] == 0x1B && buf[1] == 0 && buf[2] == 0)
		quit_nav();
	if (buf[0] == 0x1B && buf[1] == '[')
	{
		if (buf[2] == 'D')
			prev_choice(&current);
		else if (buf[2] == 'C')
			next_choice(&current);
		else if (buf[2] == 'A')
			up_choice(&current);
		else if (buf[2] == 'B')
			down_choice(&current);
	}
}
