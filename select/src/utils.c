/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:09:19 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/04 20:16:15 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_select.h"

int		ft_tputchar(int c)
{
	return (write(STDERR_FILENO, &c, 1));
}

void	clean_exit(void)
{
	reset_term();
	clean_choices();
	exit(0);
}
