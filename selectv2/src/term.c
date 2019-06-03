/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 15:49:06 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/03 22:29:17 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <term.h>
#include <sys/ioctl.h>
#include "select.h"

int	apply_termios(struct termios *term)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, term) == -1)
		return (0);
	return (1);
}

int	setup_term(t_select *select)
{
	if (tcgetattr(STDIN_FILENO, &select->def_term) == -1)
		return (0);
	ft_memcpy(&select->custom_term, &select->def_term, sizeof(struct termios));
	select->custom_term.c_lflag &= ~(ICANON | ECHONL);
	select->custom_term.c_cc[VMIN] = 1;
	select->custom_term.c_cc[VTIME] = 0;
	return (apply_termios(&select->custom_term));
}

int	update_winsize(t_select *select)
{
	int	ret;

	ret = 1;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &select->winsize) == -1)
		ret = 0;
	if (!ret || select->winsize.ws_col == 0)
		select->winsize.ws_col = tgetnum("co");
	if (!ret || select->winsize.ws_row == 0)
		select->winsize.ws_row = tgetnum("li");
	return (ret);
}
