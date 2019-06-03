/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 15:49:06 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/03 17:04:49 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "select.h"
#include <unistd.h>
#include <term.h>

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
	select->custom_term.c_lflag &= ~(ICANON | ECHONL | ISIG);
	select->custom_term.c_cc[VMIN] = 1;
	select->custom_term.c_cc[VTIME] = 0;
	return (apply_termios(&select->custom_term));
}
