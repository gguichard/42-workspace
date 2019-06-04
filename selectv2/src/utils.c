/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 22:33:52 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/04 12:52:02 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "select.h"

extern t_select	*g_select;

int				t_putchar(int c)
{
	return (write(g_select->tty_fd, &c, 1));
}
