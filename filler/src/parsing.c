/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 11:44:04 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/13 09:28:01 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include "filler.h"

void		*read_player(t_filler *filler)
{
	char	*line;
	char	**parts;

	if (get_next_line(STDIN_FILENO, &line) < 0)
		return (NULL);
	parts = ft_strsplit(line, ' ');
	free(line);
	if (!ft_strequ(parts[0], "$$$") || !ft_strequ(parts[1], "exec"))
		return (ft_strtab_free(parts));
	if (!ft_strequ(parts[2], "p1") && !ft_strequ(parts[2], "p2"))
		return (ft_strtab_free(parts));
	filler->player = (parts[2][1] == '1') ? 'O' : 'X';
	filler->opp = filler->player == 'O' ? 'X' : 'O';
	ft_strtab_free(parts);
	return (filler);
}
